/*struct MyCollection {
    size: usize,
    data: std::Vec<u8>,
}

impl MyCollection {
    fn iter(&self) -> &u8;
    fn iter_mut(&mut self) -> &mut u8;
    fn into_iter(self) -> u8;
}
*/
struct ForwardCounter {
    count: isize,
    limit: isize,
}

impl ForwardCounter {
    fn new(count: isize, limit: isize) -> Self {
        if count >= limit {
            panic!("count({}) sould be < then limit({})", count, limit);
        }

        Self { count, limit }
    }
}

impl Iterator for ForwardCounter {
    type Item = isize;

    fn next(&mut self) -> Option<Self::Item> {
        if self.count < self.limit {
            let ret = self.count;
            self.count += 1;
            Some(ret)
        } else {
            None
        }
    }
}

struct BackwardCounter {
    count: isize,
    limit: isize,
}

impl BackwardCounter {
    fn new(count: isize, limit: isize) -> Self {
        if count <= limit {
            panic!("count({}) sould be > then limit({})", count, limit);
        }

        Self { count, limit }
    }
}

impl Iterator for BackwardCounter {
    type Item = isize;

    fn next(&mut self) -> Option<Self::Item> {
        if self.count > self.limit {
            let ret = self.count;
            self.count -= 1;
            Some(ret)
        } else {
            None
        }
    }
}

fn main() {
    println!("forward iter [10, 22):");
    let mut c = ForwardCounter::new(10, 22);
    while let Some(item) = c.next() {
        println!("forward: {item}");
    }

    println!("\nbackward iter [22, 15):");
    let c = BackwardCounter::new(22, 15);
    for x in c {
        println!("backward: {x}");
    }

    // IntoIterator trait.
    // for loop by default uses IntoIterator::into_iter on collections
    // which consumes an iterator.
    // let's check it.
    let mut v = vec![1, 2, 3, 4, 5];
    println!("\n\nIntoIterator::into_iter() before. v: {:?}", v);
    /*
        x in v  is the same as v.into_iter()
        x in &v                v.iter()
        x in &mut v            v.iter_mut()
    */
    for x in &mut v {
        // v      -> IntoIterator::into_iter(), consuming iterator
        // &v     -> uses iter() which returns &T, borrowing shared iterator
        // &mut v -> uses iter_mut() which returns &mut T, borrowing mutable iterator
        *x += 2;
        println!("x: {x}");
    }
    println!("IntoIterator::into_iter() after. v: {:?}", v);

    let infinite_numbers = 0..;
    let five_numbers = infinite_numbers.take(5);
    for n in five_numbers {
        println!("n: {n}");
    }

    let ones = std::iter::repeat(1);
    let min = ones.min().unwrap(); // <- infinite loop
    println!("min: {min}");

    /*
    TODO:

    impl<C> IntoIterator for C<&T> {}
    impl<C> IntoIterator for C<&mut T> {}
    impl IntoIterator for &C;
    impl IntoIterator for &mut C;
    */
}

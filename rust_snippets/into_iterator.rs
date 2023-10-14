fn collect_as_string<T>(collection: T) -> Vec<String>
where
    T: IntoIterator,
    T::Item: std::fmt::Debug,
{
    collection
        .into_iter()
        .map(|item| format!("{item:?}"))
        .collect()
}

#[derive(Debug)]
struct MyCollection(Vec<i32>);

impl MyCollection {
    fn new() -> MyCollection {
        MyCollection(Vec::new())
    }

    fn add(&mut self, elem: i32) {
        self.0.push(elem)
    }
}

impl IntoIterator for MyCollection {
    type Item = i32;
    type IntoIter = std::vec::IntoIter<Self::Item>;

    fn into_iter(self) -> Self::IntoIter {
        self.0.into_iter()
    }
}

fn main() {
    let mut c = MyCollection::new();

    c.add(0);
    c.add(1);
    c.add(2);

    for (i, n) in c.into_iter().enumerate() {
        assert_eq!(i as i32, n);
    }

    let mut c2 = MyCollection::new();
    c2.add(100);
    c2.add(101);
    c2.add(102);
    let c2_string = collect_as_string(c2);
    // println!("c2: {:?}", c2); /// move occurs because `c2` has type `MyCollection`, which does not implement the `Copy` trait
    println!("c2_string: {:?}", c2_string);
}
struct Node<T> {
    next: *mut Node<T>,
    prev: *mut Node<T>,
    data: T,
}

pub struct LinkedList<T> {
    first: *mut Node<T>,
    last: *mut Node<T>,
    _marker: std::marker::PhantomData<T>,
}

unsafe fn raw_into_box<T>(r: *mut T) -> Box<T> {
    std::mem::transmute(r)
}

fn box_into_raw<T>(b: Box<T>) -> *mut T {
    unsafe { std::mem::transmute(b) }
}

impl<T> LinkedList<T> {
    pub fn new() -> Self {
        LinkedList {
            first: std::ptr::null_mut(),
            last: std::ptr::null_mut(),
            _marker: std::marker::PhantomData,
        }
    }

    pub fn push_back(&mut self, t: T) {
        let new = Box::new(Node {
            data: t,
            next: std::ptr::null_mut(),
            prev: self.last,
        });
        let new = box_into_raw(new);

        if self.last.is_null() {
            debug_assert!(self.first.is_null());
            self.first = new;
        } else {
            debug_assert!(!self.first.is_null());
            unsafe {
                (*self.last).next = new;
            }
        }

        self.last = new;
    }

    pub fn append(&mut self, t: T) {
        self.push_back(t);
    }

    pub fn push_front(&mut self, t: T) {
        let new = Box::new(Node {
            data: t,
            next: self.first,
            prev: std::ptr::null_mut(),
        });
        let new = box_into_raw(new);

        self.first = new;
        /*
        if self.last.is_null() {
            self.last = new;
        }
        */
    }

    pub fn prepend(&mut self, t: T) {
        self.push_front(t);
    }

    /*
    pub fn pop_back(&mut self) -> Option<T> {
        // FIXME:
        Some(Default::default())
    }

    pub fn pop_front(&mut self) -> Option<T> {
        // FIXME:
        Some(Default::default())
    }
    */

    pub fn iter_mut(&mut self) -> IterMut<T> {
        IterMut {
            next: self.first,
            _marker: std::marker::PhantomData,
        }
    }

    pub fn count(&self) -> usize {
        let mut cnt = 0;

        let mut cur_ptr = self.first;
        while !cur_ptr.is_null() {
            cnt += 1;
            cur_ptr = unsafe { (*cur_ptr).next };
        }

        cnt
    }

    pub fn is_empty(&self) -> bool {
        self.first.is_null() && self.last.is_null()
    }
}

pub struct IterMut<'a, T>
where
    T: 'a,
{
    next: *mut Node<T>,
    _marker: std::marker::PhantomData<&'a mut LinkedList<T>>,
}

impl<'a, T> Iterator for IterMut<'a, T> {
    type Item = &'a mut T;

    fn next(&mut self) -> Option<Self::Item> {
        if self.next.is_null() {
            None
        } else {
            let next = unsafe { &mut *self.next };
            let ret = &mut next.data;
            self.next = next.next;
            Some(ret)
        }
    }
}

impl<T> Drop for LinkedList<T> {
    fn drop(&mut self) {
        let mut cur_ptr = self.first;
        while !cur_ptr.is_null() {
            let cur = unsafe { raw_into_box(cur_ptr) };
            cur_ptr = cur.next;
            drop(cur);
        }
    }
}

impl<T> std::fmt::Display for LinkedList<T>
where
    T: std::fmt::Display + Copy,
{
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        if self.first.is_null() {
            write!(f, "EMPTY")?;
        } else {
            let mut s = String::new();
            let mut cur_ptr = self.first;
            while !cur_ptr.is_null() {
                s += &format!("{} -> ", unsafe { (*cur_ptr).data });
                cur_ptr = unsafe { (*cur_ptr).next };
            }
            s += &format!(".");
            write!(f, "{}", s)?;
        }
        Ok(())
    }
}

fn main() {
    let mut l = LinkedList::<u32>::new();

    fn debug_list<T>(msg: &str, l: &LinkedList<T>)
    where
        T: std::marker::Copy + std::fmt::Display,
    {
        println!("\n==================================");
        println!("{}", msg);
        println!("l.is_empty(): {}", l.is_empty());
        println!("l.count(): {}", l.count());
        println!("{}", *l);
    }

    debug_list("initial", &l);
    l.append(22);
    debug_list("append(22)", &l);
    l.append(33);
    debug_list("append(33):", &l);

    l.prepend(4);
    debug_list("prepend(4):", &l);
    l.prepend(3);
    debug_list("prepend(3):", &l);
    l.prepend(2);
    debug_list("prepend(2):", &l);
    l.prepend(1);
    debug_list("prepend(1):", &l);
}

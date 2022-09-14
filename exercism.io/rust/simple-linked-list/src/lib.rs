use std::iter::FromIterator;

pub struct SimpleLinkedList<T> {
    first: *mut Node<T>,
    len: usize,
}

struct Node<T> {
    data: T,
    next: *mut Node<T>,
}

fn box_into_raw<T>(b: Box<T>) -> *mut T {
    unsafe { std::mem::transmute(b) }
}

unsafe fn raw_into_box<T>(p: *mut T) -> Box<T> {
    std::mem::transmute(p)
}

impl<T> SimpleLinkedList<T> {
    pub fn new() -> Self {
        SimpleLinkedList {
            first: std::ptr::null_mut(),
            len: 0,
        }
    }

    pub fn is_empty(&self) -> bool {
        self.first.is_null()
    }

    pub fn len(&self) -> usize {
        self.len
    }

    pub fn push(&mut self, t: T) {
        let n = Box::new(Node {
            data: t,
            next: self.first,
        });
        self.first = box_into_raw(n);

        self.len += 1;
    }

    pub fn pop(&mut self) -> Option<T> {
        if self.is_empty() {
            return None;
        }

        let first = unsafe { raw_into_box(self.first) };
        self.first = unsafe { (*self.first).next };
        self.len -= 1;
        Some(first.data)
    }

    pub fn peek(&self) -> Option<&T> {
        if self.is_empty() {
            return None;
        }

        Some(unsafe { &(*self.first).data })
    }

    pub fn rev(mut self) -> SimpleLinkedList<T> {
        let mut new = SimpleLinkedList::new();

        while !self.is_empty() {
            new.push(self.pop().unwrap());
        }

        new
    }
}

impl<T> Drop for SimpleLinkedList<T> {
    fn drop(&mut self) {
        let mut cur_ptr = self.first;
        while !cur_ptr.is_null() {
            let cur = unsafe { raw_into_box(cur_ptr) };
            cur_ptr = unsafe { (*cur_ptr).next };
            drop(cur);
        }
    }
}

impl<T> FromIterator<T> for SimpleLinkedList<T> {
    fn from_iter<I: IntoIterator<Item = T>>(iter: I) -> Self {
        let mut lst = SimpleLinkedList::new();
        for x in iter {
            lst.push(x);
        }
        lst
    }
}

// In general, it would be preferable to implement IntoIterator for SimpleLinkedList<T>
// instead of implementing an explicit conversion to a vector. This is because, together,
// FromIterator and IntoIterator enable conversion between arbitrary collections.
// Given that implementation, converting to a vector is trivial:
//
// let vec: Vec<_> = simple_linked_list.into_iter().collect();
//
// The reason this exercise's API includes an explicit conversion to Vec<T> instead
// of IntoIterator is that implementing that interface is fairly complicated, and
// demands more of the student than we expect at this point in the track.

impl<T: std::fmt::Display> From<SimpleLinkedList<T>> for Vec<T> {
    fn from(mut linked_list: SimpleLinkedList<T>) -> Vec<T> {
        let mut v: Vec<T> = Vec::with_capacity(linked_list.len());

        while !linked_list.is_empty() {
            v.push(linked_list.pop().unwrap());
        }

        v.reverse();
        v
    }
}

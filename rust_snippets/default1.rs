use std::sync::{Arc, Mutex};
use std::cell::RefCell;

fn main() {
    let a: Arc<Mutex<RefCell<Vec<u8>>>> = <_>::default();
    dbg!(&a);

    let b = a.clone();
    dbg!(&b);
}

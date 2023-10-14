const TEST: std::cell::RefCell<Option<i32>> = std::cell::RefCell::new(None);

fn main() {
    let _ = TEST.borrow_mut().insert(42);
    match TEST.borrow().as_ref() {
        Some(x) => println!("Value is: {:?}", x),
        None => println!("SHIT!!!"),
    }
}

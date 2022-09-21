use std::{thread, time};

fn main() {
    let pause = time::Duration::from_millis(20);
    let handle1 = thread::spawn(move || {
        thread::sleep(pause);
        println!("handle1");
    });
    let handle2 = thread::spawn(move || {
        thread::sleep(pause);
        println!("handle2");
    });

    handle1.join().unwrap();
    handle2.join().unwrap();
}

use std::{thread, time};

fn main() {
    let pause = time::Duration::from_millis(20);
    let handle_1 = thread::spawn(move || {
        thread::sleep(pause);
    });

    let handle_2 = thread::spawn(move || {
        thread::sleep(pause);
    });

    handle_1.join().unwrap();
    handle_2.join().unwrap();

    println!("finish. all done.");
}

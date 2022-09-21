use std::{thread, time};

fn main() {
    let start = time::Instant::now();

    let handler1 = thread::spawn(|| {
        let pause = time::Duration::from_millis(300);
        thread::sleep(pause/*.clone()*/);
    });

    let handler2 = thread::spawn(|| {
        let pause = time::Duration::from_millis(300);
        thread::sleep(pause/*.clone()*/);
    });

    handler1.join().unwrap();
    handler2.join().unwrap();

    let finish = time::Instant::now();

    println!("{:02?}", finish.duration_since(start));
}

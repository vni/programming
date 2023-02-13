use std::sync::{Arc, Mutex};
use std::thread;

fn main() {
    println!("Arc<Mutex<i32>>");

    let data = Arc::new(Mutex::new(0_i32));
    println!("data: {}", *data.lock().unwrap());

    let d1 = data.clone();
    let t1 = thread::spawn(move || {
        for _ in 0..1_000_000 {
            *d1.lock().unwrap() += 1;
        }
        
    });

    let d2 = Arc::clone(&data);
    let t2 = thread::spawn(move || {
        for _ in 0..1_000_000 {
            *d2.lock().unwrap() += 1;
        }
    });

    t1.join().expect("thread1 finished with error or panic");
    t2.join().expect("thread2 finished with error or panic");

    println!("data: {}", *data.lock().unwrap());
}

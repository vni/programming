use std::{thread, time::Instant, time::Duration};

fn main() {
    for n in 1..101 {
        let mut handlers: Vec<thread::JoinHandle<()>> = Vec::with_capacity(n);

        let start = Instant::now();
        for _m in 0..n {
            let handle = thread::spawn(|| {
                let start = Instant::now();
                let pause = Duration::from_millis(20);
                while start.elapsed() < pause {
                    thread::yield_now();
                }
            });

            handlers.push(handle);
        }

        for handle in handlers {
            handle.join().unwrap();
        }

        let finish = Instant::now();
        println!("{}\t{:02?}", n, finish.duration_since(start));
    }
}

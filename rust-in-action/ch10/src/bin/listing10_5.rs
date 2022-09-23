use std::{thread, time};

fn main() {
    for n in 1..1001 {
        let mut handlers: Vec<thread::JoinHandle<()>> = Vec::with_capacity(n);

        let start = time::Instant::now();

        for _m in 0..n {
            let handle = thread::spawn(|| {
                let start = time::Instant::now();
                let pause = time::Duration::from_millis(20);

                while start.elapsed() < pause {
                    thread::yield_now();
                    // std::sync::atomic::spin_loop_hint(); // deprecated
                    // std::hint::spin_loop();
                }
            });

            handlers.push(handle);
        }

        /*
        while let Some(handle) = handlers.pop() {
            handle.join().unwrap();
        }
        */

        // for handle in &handlers {
        for handle in handlers {
            handle.join().unwrap();
        }

        let finish = time::Instant::now();
        println!("{}\t{:02?}", n, finish.duration_since(start));
    }
}

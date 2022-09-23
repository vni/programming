#[macro_use]
extern crate crossbeam;

use crossbeam::channel::unbounded;
use std::thread;

fn main() {
    let (tx, rx) = unbounded();

    thread::spawn(move || {
        println!("tx thr");
        thread::sleep(std::time::Duration::from_secs(1));
        tx.send(42).unwrap();
        println!("tx thr. data sent.");
    });

    select! {
        recv(rx) -> msg => {
            let msg = msg.unwrap();
            println!("recv(rx) msg: {:?}", msg)
        },
    }
}

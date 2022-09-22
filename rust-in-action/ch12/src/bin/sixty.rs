/*
 * from another terminal
 *
 * $ kill -SIGSTOP <pid>
 * <wait a little bit>
 * $ kill -SIGCONT <pid>
 *
 *
 * $ kill -SIGTSTP <pid>
 * <wait a little bit>
 * $ kill -SIGCONT <pid>
 */
use std::{process, thread::sleep, time};

fn main() {
    let delay = time::Duration::from_secs(1);

    let pid = process::id();
    println!("process id: {pid}");

    for i in 1..=60 {
        sleep(delay);
        println!(". {i}");
    }
}

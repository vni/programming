use rand;
use std::io::Write; // import trait
use std::thread::sleep;
use std::time::Duration;

static mut SHUT_DOWN: u8 = 0;

fn main() {
    let delay = Duration::from_millis(200);
    loop {
        unsafe {
            SHUT_DOWN = rand::random();
        }
        sleep(delay);
        print!(".");
        std::io::stdout().flush().expect("Failed to flush stdout");

        if unsafe { SHUT_DOWN < 10 } {
            break;
        };
    }

    println!("Done");
}

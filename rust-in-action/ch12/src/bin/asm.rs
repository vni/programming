// #![feature(asm)]

use std::arch::asm;

fn main() {
    println!("before int 42");
    unsafe {
        asm!("int 42");
    }
    println!("asfter int 42");
}

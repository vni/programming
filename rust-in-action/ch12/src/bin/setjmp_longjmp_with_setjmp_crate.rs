// This example uses setjmp crate because I fail to make
// original code (neither from the book neither from the
// book's github) to compile.
#![cfg(not(windows))]

use setjmp::{jmp_buf, longjmp, setjmp};
use std::mem::MaybeUninit;

static mut SHUT_DOWN: bool = false;
static mut RETURN_HERE: MaybeUninit<jmp_buf> = MaybeUninit::uninit();
const MOCK_SIGNAL_AT: usize = 8;

#[inline]
fn return_early() {
    unsafe { longjmp(RETURN_HERE.as_mut_ptr(), 1) };
}

fn register_signal_handler() {
    unsafe { libc::signal(libc::SIGUSR1, handle_signals as usize) };
}

#[allow(dead_code)]
fn handle_signals(sig: i32) {
    register_signal_handler();

    println!("handle_signals: sig: {sig}");

    let should_shut_down = match sig {
        libc::SIGHUP => false,
        libc::SIGALRM => false,
        libc::SIGTERM => true,
        libc::SIGQUIT => true,
        libc::SIGUSR1 => true,
        _ => false,
    };

    unsafe { SHUT_DOWN = should_shut_down };

    return_early();

    println!("handle_signals(): *ERROR*");
}

fn print_depth(depth: usize) {
    for _ in 0..depth {
        print!("#");
    }

    println!();
}

fn dive(depth: usize, max_depth: usize) {
    if unsafe { SHUT_DOWN } {
        println!("!");
        return;
    }

    print_depth(depth);

    if depth >= max_depth {
        return;
    }

    if depth == MOCK_SIGNAL_AT {
        unsafe { libc::raise(libc::SIGUSR1) };
    }

    dive(depth + 1, max_depth);
    print_depth(depth);
}

fn main() {
    register_signal_handler();

    const JUMP_SET: i32 = 0;

    let rc = unsafe { setjmp(RETURN_HERE.as_mut_ptr()) };
    if rc == JUMP_SET {
        dive(0, 10);
    } else {
        println!("early return. rc: {rc}");
    }

    println!("finishing!");
}

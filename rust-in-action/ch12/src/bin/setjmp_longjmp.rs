#![feature(link_llvm_intrinsics)]
#![allow(non_camel_case_types)]
#![cfg(not(windows))]

const JMP_BUF_WIDTH: usize = std::mem::size_of::<usize>() * 8;
type jmp_buf = [i8; JMP_BUF_WIDTH];

static mut SHUT_DOWN: bool = false;
static mut RETURN_HERE: jmp_buf = [0; JMP_BUF_WIDTH];
const MOCK_SIGNAL_AT: usize = 3;

extern "C" {
    #[link_name = "llvm.eh.sjlj.setjmp"]
    pub fn setjmp(_: *mut i8) -> i32;

    #[link_name = "llvm.eh.sjlj.longjmp"]
    pub fn longjmp(_: *mut i8);
}

#[inline]
fn ptr_to_jmp_buf() -> *mut i8 {
    unsafe { &RETURN_HERE as *const i8 as *mut i8 }
    // unsafe { &mut RETURN_HERE as *mut i8 }
}

#[inline]
fn return_early() {
    let franken_pointer = ptr_to_jmp_buf();
    unsafe { longjmp(franken_pointer) };
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

    // return_early();

    println!("handle_signals(): *ERROR*");
}

fn print_depth(depth: usize) {
    for _ in 0..depth {
        print!("#");
    }

    println!();
}

fn dive(depth: usize, max_depth: usize) {
    /*
    if unsafe { SHUT_DOWN } {
        println!("!");
        return;
    }
        */

    print_depth(depth);

    if depth >= max_depth {
        return;
    }

    if depth == MOCK_SIGNAL_AT {
        unsafe { libc::raise(libc::SIGUSR1) };
        //return_early();
    }

    dive(depth + 1, max_depth);
    print_depth(depth);
}

fn main() {
    register_signal_handler();

    const JUMP_SET: i32 = 0;

    let return_point = ptr_to_jmp_buf();
    let rc = unsafe { setjmp(return_point) };
    if rc == JUMP_SET {
        dive(0, 10);
    } else {
        println!("early return");
    }

    println!("finishing!");

    return_early();
}

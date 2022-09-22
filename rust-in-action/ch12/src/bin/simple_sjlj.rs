#![feature(link_llvm_intrinsics)]
#![allow(non_camel_case_types)]
#![cfg(not(windows))]

const JMP_BUF_WIDTH: usize = std::mem::size_of::<usize>() * 512;
type jmp_buf = [i8; JMP_BUF_WIDTH];

extern "C" {
    #[link_name = "llvm.eh.sjlj.setjmp"]
    pub fn setjmp(_: *mut i8) -> i32;

    #[link_name = "llvm.eh.sjlj.longjmp"]
    pub fn longjmp(_: *mut i8) -> ();
}

fn main() {
    println!("JMP_BUF_WIDTH: {JMP_BUF_WIDTH}");
    let mut jbuf: jmp_buf = [0_i8; JMP_BUF_WIDTH];

    let rc = unsafe { setjmp(&mut jbuf as *mut i8) };
    if rc == 0 {
        println!("default mode");
        for i in 0..16 {
            println!("i: {i}");

            if i > 12 {
                unsafe { longjmp(&mut jbuf as *mut i8) };
            }
        }
    } else {
        println!("after setjmp: rc != 0: rc == {rc}");
    }
}

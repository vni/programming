use setjmp::{jmp_buf, longjmp, setjmp};
use std::mem::MaybeUninit;

fn main() {
    //let mut jmpbuf: setjmp::jmp_buf = [setjmp::sys::__jmp_buf_tag::default(); 1];
    let mut jmpbuf: MaybeUninit<jmp_buf> = MaybeUninit::uninit();

    //let rc = unsafe { setjmp(&mut jmpbuf) };
    let rc = unsafe { setjmp(jmpbuf.as_mut_ptr()) };
    if rc == 0 {
        println!("initial setjmp. rc is 0");
    } else {
        println!("HOLY SHIT! It works. rc: {rc}");
        return;
    }

    //unsafe { longjmp(&mut jmpbuf, 15) };
    unsafe { longjmp(jmpbuf.as_mut_ptr(), 25) };
}

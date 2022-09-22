fn main() -> () {
    unsafe {
        libc::signal(libc::SIGTERM, libc::SIG_IGN);
        libc::raise(libc::SIGTERM);
    }

    println!("ok");

    unsafe {
        libc::signal(libc::SIGTERM, libc::SIG_DFL);
        libc::raise(libc::SIGTERM);
    }

    println!("not ok");
    unreachable!();
}

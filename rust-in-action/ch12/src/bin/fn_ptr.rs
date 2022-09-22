fn noop() {}

fn main() {
    println!();
    println!("fn ptr as usize");
    let fn_ptr = noop as usize;
    println!("noop as usize: 0x{:x}", fn_ptr);
    println!("main as usize: 0x{:x}", main as usize);

    println!();
    println!("fn ptr as *const fn() -> ()");
    let typed_fn_ptr = noop as *const fn() -> ();
    println!("noop as *const fn() -> (): {:p}", typed_fn_ptr);
    println!("main as *const fn() -> (): {:p}", main as *const fn() -> ());
}

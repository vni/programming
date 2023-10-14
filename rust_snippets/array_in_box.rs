fn main() {
    let b: Box<[u16]> = Box::new([55 as u16; 1000]);
    println!("std::mem::size_of_val(&*b): {}", std::mem::size_of_val(&*b));
}

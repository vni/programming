fn main() {
    let r: &mut i32 = &mut 92;
    println!("r: {}", r);
    *r += 1;
    println!("r: {}", r);
}

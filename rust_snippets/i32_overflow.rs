fn main() {
    let x = i32::max_value();
    let y = x + 1;
    println!("x: {}", x);
    println!("y: {}", y);

    let x = i32::max_value();
    let y = x.wrapping_add(1);
    println!("i32::max_value(): {}", x);
    println!("x: {}", x);
    println!("x.wrapping_add(1): {}", y);
    println!("i32::min_value(): {}", i32::min_value());
    assert_eq!(y, i32::min_value());

    let y = x.saturating_add(1);
    println!("x.saturation_add(1): {}", y);
    assert_eq!(y, i32::max_value());

    let (y, overflowed) = x.overflowing_add(1);
    println!("y: {}, overflowed: {}", y, overflowed);
    assert!(overflowed);
    assert_eq!(y, i32::min_value());

    match x.checked_add(1) {
        Some(_y) => unreachable!(),
        None => println!("overflowed"),
    }
}

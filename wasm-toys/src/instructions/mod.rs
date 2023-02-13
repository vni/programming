pub mod i32;

// 0x00
pub fn x_unreachable() {
    println!("unreachable. What to do here?");
}

pub fn x_block() {
    unimplemented!();
}

pub fn x_loop() {
    unimplemented!();
}

// 0x01
pub fn x_nop() {
    unimplemented!();
}

//
pub fn x_reserved() {
    panic!("reserved instruction occured");
}

// 0xfd
pub fn x_reserved_extended_simd() {
    unimplemented!();
}

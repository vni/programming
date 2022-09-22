#[allow(unused)]
fn interrupt_handler() {
    println!("> interrupt_handler <");
}

fn add(a: i32, b: i32) -> i32 {
    a + b
}

fn main() {
    let a = 5;
    let b = 6;

    // Key pressed on keyboard;
    interrupt_handler();

    let c = add(a, b);
    println!("c: {c}");
}

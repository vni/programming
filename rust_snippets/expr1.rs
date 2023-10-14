fn main() {
    let y = 1 + { let x = 2; x * 2 };
    println!("y: {y}");

    let i: i32 = { 1 };
    println!("i: {i}");
    let j: () = { 1; };
    println!("j: {j:?}");

    let x: () = while false { 1; };
    println!("x: {x:?}");
}

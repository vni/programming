fn fib(i: u128) -> u128 {
    match i {
        0 => 0,
        1 => 1,
        _ => i * fib(i - 1),
    }
}

fn main() {
/*
    println!("fib(5): {}", fib(5));
    println!("fib(10): {}", fib(10));
    println!("fib(20): {}", fib(20));
    println!("fib(25): {}", fib(25));
    println!("fib(30): {}", fib(30));
    println!("fib(40): {}", fib(40));
*/

    for i in 0.. {
        println!("fib({i}): {}", fib(i));
    }
}

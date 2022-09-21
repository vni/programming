fn add(a: i32, b: i32) -> i32 {
    a + b
}

fn main() {
    let lambda_add = |a, b| { a + b };

    println!("add(4, 5): {}", add(4, 5));
    println!("lambda_add(4, 5): {}", lambda_add(4, 5));

    assert_eq!(add(4, 5), lambda_add(4, 5));
}

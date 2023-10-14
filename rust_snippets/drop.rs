fn drop<T>(_value: T) {
}

fn main() {
    let x = Box::new(1);
    let y = Box::new(2);
    println!("x: {x}");
    println!("y: {y}");
    drop(x);
    drop(y);
}

fn main() {
    let mut message = "Hello, world!".to_string();

    println!("before>  message: {}", message);
    message.extend(&['a', 'b', 'c']);
    println!("after>   message: {}", message);
}

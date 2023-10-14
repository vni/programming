fn main() {
    let void_result = println!("hello");
    assert_eq!(void_result, ());
    println!("void_result: `{:?}`", void_result);
}

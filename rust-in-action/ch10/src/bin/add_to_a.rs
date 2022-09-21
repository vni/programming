fn main() {
    let a = 20;

    let add_to_a = |b| { a + b };
    //add_to_a == ();
    //^^^^^^^^
    //[closure@ch10/src/bin/add_to_a.rs:4:20: 4:33]
    //error[E0369]: binary operation `==` cannot be applied to type `[closure@ch10/src/bin/add_to_a.rs:4:20: 4:33]`
    println!("add_to_a(3): {}", add_to_a(3));
}

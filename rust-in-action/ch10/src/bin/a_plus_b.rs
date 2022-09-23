// a small snippet just that shows how to deduce
// the var type during compile time

/*
error[E0369]: binary operation `==` cannot be applied to type `[closure@ch10/src/bin/a_plus_b.rs:3:20: 3:23]`
 --> ch10/src/bin/a_plus_b.rs:4:14
  |
4 |     add_to_a == ();
  |     -------- ^^ -- ()
  |     |
  |     [closure@ch10/src/bin/a_plus_b.rs:3:20: 3:23]
*/
fn main() {
    let a = 20;
    let add_to_a = |b| a + b;
    add_to_a == ();
}

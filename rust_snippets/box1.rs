fn main() {
    let a: Box<i32>;
    a = Box::new(1);
    bar(&*a);
    bar(&a);
}

fn bar(b: &i32) {
    println!("b: {:p}", b);
}

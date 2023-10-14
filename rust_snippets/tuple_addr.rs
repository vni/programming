fn main() {
    let t = (92,);
    println!("{:?}", &t as *const (i32,));
    println!("{:?}", &t.0 as *const i32);
}

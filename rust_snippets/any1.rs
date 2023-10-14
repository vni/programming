use std::any::{Any, TypeId};

fn main() {
    let boxed: Box<dyn Any> = Box::new(99_u32);
    let actual_id = (&*boxed).type_id();
    let boxed_id = boxed.type_id();

    println!("actual_id: {:?}", actual_id);
    println!("boxed_id: {:?}", boxed_id);
}

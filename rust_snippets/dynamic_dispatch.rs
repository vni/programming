trait Trait: std::fmt::Debug {
    fn method1(&self);
    fn method2(&self);
    fn method3(&self);
}

#[derive(Debug)]
struct Cat;

impl Trait for Cat {
    fn method1(&self) {
        println!("Cat::method1");
    }

    fn method2(&self) {
        println!("Cat::method2");
    }

    fn method3(&self) {
        println!("Cat::method3");
    }
}

impl std::ops::Drop for Cat {
    fn drop(&mut self) {
        println!("drop ~Cat");
    }
}

#[derive(Debug)]
struct Dog;

impl Trait for Dog {
    fn method1(&self) {
        println!("Dog::method1");
    }

    fn method2(&self) {
        println!("Dog::method2");
    }

    fn method3(&self) {
        println!("Dog::method3");
    }
}

impl std::ops::Drop for Dog {
    fn drop(&mut self) {
        println!("drop ~Dog");
    }
}

#[derive(Debug)]
struct Mice;

impl Trait for Mice {
    fn method1(&self) {
        println!("Mice::method1");
    }

    fn method2(&self) {
        println!("Mice::method2");
    }

    fn method3(&self) {
        println!("Mice::method3");
    }
}

impl std::ops::Drop for Mice {
    fn drop(&mut self) {
        println!("drop ~Mice");
    }
}

fn main() {
    let mut vec: Vec<&dyn Trait> = Vec::new();

    for v in &vec {
        println!("v: {:?}", v);
    }

    let cat = Cat;
    let dog = Dog;
    let mice = Mice;

    vec.push(&cat);
    vec.push(&dog);
    vec.push(&mice);

    for v in &vec {
        println!("v: {:?}", v);
    }

    let vec2: Vec<Box<dyn Trait>> = vec![
        Box::new(Cat), Box::new(Dog), Box::new(Mice)
    ];
    for v in &vec2 {
        v.method1();
        v.method2();
        v.method3();
    }
}

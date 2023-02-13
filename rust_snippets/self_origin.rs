struct S {
    some: u32,
    field: u32,
}

impl S {
    fn new(some: u32, field: u32) -> Self {
        Self { some, field, }
    }

    fn get_some(&self) -> u32 {
        self.some
    }

    fn get_field(&self) -> u32 {
        self.field
    }
}

impl std::fmt::Display for S {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> Result<(), std::fmt::Error> {
        write!(f, "{{ {}, {} }}", self.some, self.field)?;
        Ok(())
    }
}

fn main() {
    let s: S = S::new(10, 20);
    println!("s: {}", s);

    println!("s.get_some: {}", s.get_some());
    println!("s.get_field: {}", s.get_field())
}

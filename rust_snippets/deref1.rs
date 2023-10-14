use std::ops::{Deref, DerefMut};

struct My(Vec<u8>);

impl Deref for My {
    type Target = Vec<u8>;
    fn deref(&self) -> &Self::Target {
        &self.0
    }
}

impl DerefMut for My {
    fn deref_mut(&mut self) -> &mut Self::Target {
        &mut self.0
    }
}

fn main() {
    let mut my = My(vec![1, 2, 3, 4]);
    dbg!(my[0]);
    dbg!(my[1]);
    dbg!(my[2]);

    my[0] = 55;
    my[1] = 66;
    my[2] = 77;
    dbg!(my[0]);
    dbg!(my[1]);
    dbg!(my[2]);
}

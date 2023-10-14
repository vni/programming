use std::ops::Deref;

struct My(u8);

impl Deref for My {
    type Target = u8;
    fn deref(&self) -> &Self::Target {
        &self.0
    }
}

fn main() {
    let my = My(1);
    dbg!(&*my);
    dbg!(*my + 22);
    dbg!(&*my+1);
}

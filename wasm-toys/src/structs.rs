#[derive(Debug)]
pub struct WasmHeader {
    pub magic: u32,
    pub version: u32,
}

#[derive(Debug)]
pub struct WasmProgram {
    pub header: WasmHeader,
    pub program: Vec<u8>,
}

#[derive(Debug)]
pub struct Debug {
    pub sectionId: u8,
    pub byte_size: u32,
    pub data: Vec<u8>,
}

#[derive(Debug)]
//#[repr(C)]
pub enum SectionId {
    Custom = 0,
    Type = 1,
    Import = 2,
    Function = 3,
    Table = 4,
    Memory = 5,
    Global = 6,
    Export = 7,
    Start = 8,
    Elem = 9,
    Code = 10,
    Data = 11,
    DataCount = 12,
}

#[derive(Debug)]
pub struct DataStack(Vec<u32>);

impl DataStack {
  pub fn pop(&mut self) -> u32 {
    let x = self.0.pop();
    if x.is_none() {
      panic!("trying to pop an empty data stack");
    }
    x.unwrap()
  }

  pub fn push(&mut self, val: u32) {
    self.0.push(val);
  }
}

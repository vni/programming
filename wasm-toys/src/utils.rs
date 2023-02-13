use crate::structs::*;

use std::io::Cursor;
use byteorder::{LittleEndian, ReadBytesExt};

const WASM_HEADER_MAGIC: u32 = u32::from_le_bytes(* b"\0asm");

pub fn dump_as_hex(buf: &[u8]) {
    for i in 0..buf.len() {
        print!("{:02x} ", buf[i]);

        if (i + 1) % 16 == 0 {
            println!();
        }
    }
}

pub fn read_from_file(file_name: &str) -> WasmProgram {
    let content = std::fs::read(file_name);
    if content.is_err() {
        panic!("Failed to read the '{file_name}' program file.");
    }
    let content = content.unwrap();
    println!("'{file_name}' content len: {}", content.len());
    println!("file content:");
    dump_as_hex(&content[..]);
    println!();

    let mut cursor = Cursor::new(content);
    let magic: u32 = cursor.read_u32::<LittleEndian>().unwrap();
    let version: u32 = cursor.read_u32::<LittleEndian>().unwrap();
    //println!("magic: 0x{:08x}", magic);
    //println!("version: 0x{:08x}", version);

    if magic != WASM_HEADER_MAGIC {
        panic!("wasm file : header magic != b\"\\0asm\"");
    }

    if version != 1 {
        panic!("Don't know how to parse non-wasm-version1 binary files");
    }

    let header = WasmHeader { magic, version };

    WasmProgram {
        header,
        program: [].to_vec(),
        //program: content[8..].to_vec(),
    }
}

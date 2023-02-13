const WASM_BINARY_MAGIC: u32 = 0x0061_736d;
const WASM_BINARY_VERSION: u32 = 0x0100_0000;

fn read_file(filename: &str) -> Vec<u8> {
    let content = std::fs::read(filename);
    if content.is_err() {
        panic!("Failed to read the '{filename}' wasm file");
    }
    content.unwrap()
}
/*
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
*/

fn main() {
    let args = std::env::args().collect::<Vec<String>>();
    if args.len() != 2 {
        panic!("Expect filename in the command line");
    }

    let filename: &str = args[1].as_str();

    let content = read_file(filename);

    println!("content size: {}", content.len());

    parse(&content[..]);
}

struct Header {
    magic: u32,
    version: u32,
}

struct Section<'a> {
    id: u8,
    size: u32,
    data: &'a [u8],
}

pub fn dump_as_hex(buf: &[u8]) {
    for i in 0..buf.len() {
        print!("{:02x} ", buf[i]);

        if (i + 1) % 16 == 0 {
            println!();
        }
    }
}

fn parse_custom_section(id: u8, size: u32, data: &[u8]) {
    // id 0
}

fn parse_type_section(id: u8, size: u32, data: &[u8]) {
    // id 1
}

fn parse_import_section(id: u8, size: u32, data: &[u8]) {
    // id 2
}

fn parse_function_section(id: u8, size: u32, data: &[u8]) {
    // id 3
}

fn parse_table_section(id: u8, size: u32, data: &[u8]) {
    // id 4
}

fn parse_memory_section(id: u8, size: u32, data: &[u8]) {
    // id 5
}

fn parse_global_section(id: u8, size: u32, data: &[u8]) {
    // id 6
}

fn parse_export_section(id: u8, size: u32, data: &[u8]) {
    // id 7
}

fn parse_start_section(id: u8, size: u32, data: &[u8]) {
    // id 8
}

fn parse_element_section(id: u8, size: u32, data: &[u8]) {
    // id 9
}

fn parse_code_section(id: u8, size: u32, data: &[u8]) {
    // id 10
}

fn parse_data_section(id: u8, size: u32, data: &[u8]) {
    // id 11
}

fn parse_data_count_section(id: u8, size: u32, data: &[u8]) {
    // id 12
}

fn parse(content: &[u8]) {
    use std::io::Cursor;
    use byteorder::{LittleEndian, ReadBytesExt};

    let mut cursor = Cursor::new(content);

    let magic: u32 = cursor.read_u32::<LittleEndian>().unwrap();
    let version: u32 = cursor.read_u32::<LittleEndian>().unwrap();

    let section_id: u8 = cursor.read_u8().unwrap();
    let section_size: u32 = cursor.read_u32::<LittleEndian>().unwrap();

    println!("section_id: {section_id}");
    println!("section_size: {section_size}");
}

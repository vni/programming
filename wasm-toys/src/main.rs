// wasm types: i32, i64, f32, f64, v128
// opcode table: https://pengowray.github.io/wasm-ops/

// Some useful docs:
// https://github.com/WebAssembly/design/blob/main/Semantics.md

// All load and store operators use little-endian byte order when translating between values and bytes.

const MEMORY_PAGE_SIZE: usize = 65_536;

//fn interpret(command: u8) {}

//use instructions::*;
//use structs::*;

mod structs;
mod utils;
mod instructions;

// use crate::structs::*;
// use crate::utils::*;
// use crate::stack::*;
// use crate::instructions::*;
// use crate::instructions::i32::*;

//static global_variables = HashMap::new();

fn decode(program: &mut [u8], data_stack: &mut structs::DataStack) {
    for opcode in program {
        match opcode {
            0x00 => instructions::x_unreachable(),
            0x01 => instructions::x_nop(),
            0x02 => instructions::x_block(),
            0x03 => instructions::x_loop(),
            //0x04 => instructions::x_if(),
            //0x05 => instructions::x_else(),
            //0x06 => instructions::x_reserved_try(),
            //0x07 => instructions::x_reserved_catch(),
            //0x08 => instructions::x_reserved_throw(),
            //0x09 => instructions::x_reserved_rethrow(),
            //0x0a => instructions::x_reserved_br_on_exn(),
            //0x0b => instructions::x_end(),
            //0x0c => instructions::x_br(),
            //0x0d => instructions::x_br_if(),
            //0x0e => instructions::x_br_table(),
            //0x0f => instructions::x_return(),

            //0x10 => instructions::x_call(),
            //0x11 => instructions::x_call_indirect(),
            //0x12 => instructions::x_reserved_call(),
            //0x13 => instructions::x_reserved_call_indirect(),
            0x14 => instructions::x_reserved(),
            0x15 => instructions::x_reserved(),
            0x16 => instructions::x_reserved(),
            0x17 => instructions::x_reserved(),
            0x18 => instructions::x_reserved(),
            0x19 => instructions::x_reserved(),
            //0x1a => instructions::x_drop(),
            //0x1b => instructions::x_select(),
            //0x1c => instructions::x_reserved_select1(),
            0x1d => instructions::x_reserved(),
            0x1e => instructions::x_reserved(),
            0x1f => instructions::x_reserved(),

            //0x20 => instructions::x_local_get(),
            //0x21 => instructions::x_local_set(),
            //0x22 => instructions::x_local_tee(),
            //0x23 => instructions::x_global_get(),
            //0x24 => instructions::x_global_set(),
            //0x25 => instructions::x_reserved_table_get(),
            //0x26 => instructions::x_reserved_table_set(),
            0x27 => instructions::x_reserved(),
            //0x28 => instructions::x_i32_load(),
            //0x29 => instructions::x_i64_load(),
            //0x2a => instructions::x_f32_load(),
            //0x2b => instructions::x_f64_load(),
            //0x2c => instructions::x_i32_load8_s(),
            //0x2d => instructions::x_i32_load8_u(),
            //0x2e => instructions::x_i32_load16_s(),
            //0x2f => instructions::x_i32_load16_u(),

            //0x30 => instructions::x_i64_load8_s(),
            //0x31 => instructions::x_i64_load8_u(),
            //0x32 => instructions::x_i64_load16_s(),
            //0x33 => instructions::x_i64_load16_u(),
            //0x34 => instructions::x_i64_load32_s(),
            //0x35 => instructions::x_i64_load32_u(),
            //0x36 => instructions::x_i32_store(),
            //0x37 => instructions::x_i64_store(),
            //0x38 => instructions::x_f32_store(),
            //0x39 => instructions::x_f64_store(),
            //0x3a => instructions::x_i32_store8(),
            //0x3b => instructions::x_i32_store16(),
            //0x3c => instructions::x_i64_store8(),
            //0x3d => instructions::x_i64_store16(),
            //0x3e => instructions::x_i64_store32(),
            //0x3f => instructions::x_memory_size(),

            //0x40 => instructions::x_memory_grow(),
            //0x41 => instructions::x_i32_const(),
            //0x42 => instructions::x_i64_const(),
            //0x43 => instructions::x_f32_const(),
            //0x44 => instructions::x_f64_const(),
            0x45 => instructions::i32::x_i32_eqz(/*&mut */data_stack),
            0x46 => instructions::i32::x_i32_eq(/*&mut */data_stack),
            0x47 => instructions::i32::x_i32_ne(/*&mut */data_stack),
            0x48 => instructions::i32::x_i32_lt_s(/*&mut */data_stack),
            0x49 => instructions::i32::x_i32_lt_u(/*&mut */data_stack),
            0x4a => instructions::i32::x_i32_gt_s(/*&mut */data_stack),
            0x4b => instructions::i32::x_i32_gt_u(/*&mut */data_stack),
            0x4c => instructions::i32::x_i32_le_s(/*&mut */data_stack),
            0x4d => instructions::i32::x_i32_le_u(/*&mut */data_stack),
            0x4e => instructions::i32::x_i32_ge_s(/*&mut */data_stack),
            0x4f => instructions::i32::x_i32_ge_s(/*&mut */data_stack),

            //0x50 => instructions::x_i64_eqz(),
            //0x51 => instructions::x_i64_eq(),
            //0x52 => instructions::x_i64_ne(),
            //0x53 => instructions::x_i64_lt_s(),
            //0x54 => instructions::x_i64_lt_u(),
            //0x55 => instructions::x_i64_gt_s(),
            //0x56 => instructions::x_i64_gt_u(),
            //0x57 => instructions::x_i64_le_s(),
            //0x58 => instructions::x_i64_le_u(),
            //0x59 => instructions::x_i64_ge_s(),
            //0x5a => instructions::x_i64_ge_u(),
            //0x5b => instructions::x_f32_eq(),
            //0x5c => instructions::x_f32_ne(),
            //0x5d => instructions::x_f32_lt(),
            //0x5e => instructions::x_f32_gt(),
            //0x5f => instructions::x_f32_le(),

            //0x60 => instructions::x_f32_ge(),
            //0x61 => instructions::x_f64_eq(),
            //0x62 => instructions::x_f64_ne(),
            //0x63 => instructions::x_f64_lt(),
            //0x64 => instructions::x_f64_gt(),
            //0x65 => instructions::x_f64_le(),
            //0x66 => instructions::x_f64_ge(),
            0x67 => instructions::i32::x_i32_clz(/*&mut */data_stack),
            0x68 => instructions::i32::x_i32_ctz(/*&mut */data_stack),
            0x69 => instructions::i32::x_i32_popcnt(/*&mut */data_stack),
            0x6a => instructions::i32::x_i32_add(/*&mut */data_stack),
            0x6b => instructions::i32::x_i32_sub(/*&mut */data_stack),
            0x6c => instructions::i32::x_i32_mul(/*&mut */data_stack),
            0x6d => instructions::i32::x_i32_div_s(/*&mut */data_stack),
            0x6e => instructions::i32::x_i32_div_u(/*&mut */data_stack),
            0x6f => instructions::i32::x_i32_rem_s(/*&mut */data_stack),

            0x70 => instructions::i32::x_i32_rem_u(/*&mut */data_stack),
            0x71 => instructions::i32::x_i32_and(/*&mut */data_stack),
            0x72 => instructions::i32::x_i32_or(/*&mut */data_stack),
            0x73 => instructions::i32::x_i32_xor(/*&mut */data_stack),
            0x74 => instructions::i32::x_i32_shl(/*&mut */data_stack),
            0x75 => instructions::i32::x_i32_shr_s(/*&mut */data_stack),
            0x76 => instructions::i32::x_i32_shr_u(/*&mut */data_stack),
            0x77 => instructions::i32::x_i32_rotl(/*&mut */data_stack),
            0x78 => instructions::i32::x_i32_rotr(/*&mut */data_stack),
            //0x79 => instructions::x_i64_clz(),
            //0x7a => instructions::x_i64_ctz(),
            //0x7b => instructions::x_i64_popcts(),
            //0x7c => instructions::x_i64_add(),
            //0x7d => instructions::x_i64_sum(),
            //0x7e => instructions::x_i64_mul(),
            //0x7f => instructions::x_i64_div_s(),

            //0x80 => instructions::x_i64_div_u(),
            //0x81 => instructions::x_i64_rem_s(),
            //0x82 => instructions::x_i64_rem_u(),
            //0x83 => instructions::x_i64_and(),
            //0x84 => instructions::x_i64_or(),
            //0x85 => instructions::x_i64_xor(),
            //0x86 => instructions::x_i64_shl(),
            //0x87 => instructions::x_i64_shr_s(),
            //0x88 => instructions::x_i64_shr_u(),
            //0x89 => instructions::x_i64_rotl(),
            //0x8a => instructions::x_i64_rotr(),
            //0x8b => instructions::x_f32_abs(),
            //0x8c => instructions::x_f32_neg(),
            //0x8d => instructions::x_f32_ceil(),
            //0x8e => instructions::x_f32_floor(),
            //0x8f => instructions::x_f32_trunc(),

            //0x90 => instructions::x_f32_nearest(),
            //0x91 => instructions::x_f32_sqrt(),
            //0x92 => instructions::x_f32_add(),
            //0x93 => instructions::x_f32_sub(),
            //0x94 => instructions::x_f32_mul(),
            //0x95 => instructions::x_f32_div(),
            //0x96 => instructions::x_f32_min(),
            //0x97 => instructions::x_f32_max(),
            //0x98 => instructions::x_f32_copysign(),
            //0x99 => instructions::x_f64_abs(),
            //0x9a => instructions::x_f64_neg(),
            //0x9b => instructions::x_f64_ceil(),
            //0x9c => instructions::x_f64_floor(),
            //0x9d => instructions::x_f64_trunc(),
            //0x9e => instructions::x_f64_nearest(),
            //0x9f => instructions::x_f64_sqrt(),

            //0xa0 => instructions::x_f64_add(),
            //0xa1 => instructions::x_f64_sub(),
            //0xa2 => instructions::x_f64_mul(),
            //0xa3 => instructions::x_f64_div(),
            //0xa4 => instructions::x_f64_min(),
            //0xa5 => instructions::x_f64_max(),
            //0xa6 => instructions::x_f64_copysign(),
            //0xa7 => instructions::x_i32_wrap_i64(),
            //0xa8 => instructions::x_i32_trunc_f32_s(),
            //0xa9 => instructions::x_i32_trunc_f32_u(),
            //0xaa => instructions::x_i32_trunc_f64_s(),
            //0xab => instructions::x_i32_trunc_f64_u(),
            //0xac => instructions::x_i64_extend_i32_s(),
            //0xad => instructions::x_i64_extend_i32_u(),
            //0xae => instructions::x_i64_trunc_f32_s(),
            //0xaf => instructions::x_i64_trunc_f32_u(),

            //0xb0 => instructions::x_i64_trunc_f64_s(),
            //0xb1 => instructions::x_i64_trunc_f64_u(),
            //0xb2 => instructions::x_f32_convert_i32_s(),
            //0xb3 => instructions::x_f32_convert_i32_u(),
            //0xb4 => instructions::x_f32_convert_i64_s(),
            //0xb5 => instructions::x_f32_convert_i64_u(),
            //0xb6 => instructions::x_f32_demote_f64(),
            //0xb7 => instructions::x_f64_convert_i32_s(),
            //0xb8 => instructions::x_f64_convert_i32_u(),
            //0xb9 => instructions::x_f64_convert_i64_s(),
            //0xba => instructions::x_f64_convert_i64_u(),
            //0xbb => instructions::x_f64_promote_f32(),
            //0xbc => instructions::x_i32_reinterpret_f32(),
            //0xbd => instructions::x_i64_reinterpret_f64(),
            //0xbe => instructions::x_f32_reinterpret_i32(),
            //0xbf => instructions::x_f64_reinterpret_i64(),

            //0xc0 => instructions::x_reserved_i32_extend8_s(),
            //0xc1 => instructions::x_reserved_i32_extend16_s(),
            //0xc2 => instructions::x_reserved_i64_extend8_s(),
            //0xc3 => instructions::x_reserved_i64_extend16_s(),
            //0xc4 => instructions::x_reserved_i64_extend32_s(),
            0xc5 => instructions::x_reserved(),
            0xc6 => instructions::x_reserved(),
            0xc7 => instructions::x_reserved(),
            0xc8 => instructions::x_reserved(),
            0xc9 => instructions::x_reserved(),
            0xca => instructions::x_reserved(),
            0xcb => instructions::x_reserved(),
            0xcc => instructions::x_reserved(),
            0xcd => instructions::x_reserved(),
            0xce => instructions::x_reserved(),
            0xcf => instructions::x_reserved(),

            //0xd0 => instructions::x_ref_null(),
            //0xd1 => instructions::x_ref_is_null(),
            //0xd2 => instructions::x_ref_func(),
            0xd3 => instructions::x_reserved(),
            0xd4 => instructions::x_reserved(),
            0xd5 => instructions::x_reserved(),
            0xd6 => instructions::x_reserved(),
            0xd7 => instructions::x_reserved(),
            0xd8 => instructions::x_reserved(),
            0xd9 => instructions::x_reserved(),
            0xda => instructions::x_reserved(),
            0xdb => instructions::x_reserved(),
            0xdc => instructions::x_reserved(),
            0xdd => instructions::x_reserved(),
            0xde => instructions::x_reserved(),
            0xdf => instructions::x_reserved(),

            0xe0 => instructions::x_reserved(),
            0xe1 => instructions::x_reserved(),
            0xe2 => instructions::x_reserved(),
            0xe3 => instructions::x_reserved(),
            0xe4 => instructions::x_reserved(),
            0xe5 => instructions::x_reserved(),
            0xe6 => instructions::x_reserved(),
            0xe7 => instructions::x_reserved(),
            0xe8 => instructions::x_reserved(),
            0xe9 => instructions::x_reserved(),
            0xea => instructions::x_reserved(),
            0xeb => instructions::x_reserved(),
            0xec => instructions::x_reserved(),
            0xed => instructions::x_reserved(),
            0xee => instructions::x_reserved(),
            0xef => instructions::x_reserved(),

            0xf0 => instructions::x_reserved(),
            0xf1 => instructions::x_reserved(),
            0xf2 => instructions::x_reserved(),
            0xf3 => instructions::x_reserved(),
            0xf4 => instructions::x_reserved(),
            0xf5 => instructions::x_reserved(),
            0xf6 => instructions::x_reserved(),
            0xf7 => instructions::x_reserved(),
            0xf8 => instructions::x_reserved(),
            0xf9 => instructions::x_reserved(),
            0xfa => instructions::x_reserved(),
            0xfb => instructions::x_reserved(),
            //0xfc => instructions::x_reserved_extended_instruction(),
            //0xfd => instructions::x_reserved_extended_simd(),
            0xfe => instructions::x_reserved(),
            0xff => instructions::x_reserved(),

            _ => {
                println!("opcode: {opcode} is not yet implemented");
                unimplemented!()
            }
        }
    }
}

fn main() {
    //let program: &[u8] = [0x01];
    let args = std::env::args().collect::<Vec<String>>();
    if args.len() != 2 {
        panic!("Expected 1 argument: filename of wasm program to interpret.");
    }

    let filename: &str = args[1].as_str();

    let x: structs::WasmProgram = utils::read_from_file(filename);

    println!("WasmProgram: {:?}", x);
}

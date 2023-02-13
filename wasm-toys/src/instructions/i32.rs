use crate::structs::DataStack;

// 0x28
pub fn x_i32_load() {
    unimplemented!();
}

// 0x2c
pub fn x_i32_load8_s() {
    unimplemented!();
}

// 0x2d
pub fn x_i32_load8_u() {
    unimplemented!();
}

// 0x2e
pub fn x_i32_load16_s() {
    unimplemented!();
}

// 0x2f
pub fn x_i32_load16_u() {
    unimplemented!();
}

// 0x36
pub fn x_i32_store() {
    unimplemented!();
}

// 0x3a
pub fn x_i32_store8() {
    unimplemented!();
}

// 0x3b
pub fn x_i32_store16() {
    unimplemented!();
}

// 0x45
pub fn x_i32_eqz(data_stack: &mut DataStack) {
    let x = data_stack.pop();
    data_stack.push((x == 0) as u32);
}

// 0x46
pub fn x_i32_eq(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    data_stack.push((x == y) as u32);
}

// 0x47
pub fn x_i32_ne(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    data_stack.push((x != y) as u32);
}

// 0x48
pub fn x_i32_lt_s(data_stack: &mut DataStack) {
    let y = data_stack.pop() as i32;
    let x = data_stack.pop() as i32;
    data_stack.push((x < y) as u32);
}

// 0x49
pub fn x_i32_lt_u(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    data_stack.push((x < y) as u32);
}

// 0x4a
pub fn x_i32_gt_s(data_stack: &mut DataStack) {
    let y = data_stack.pop() as i32;
    let x = data_stack.pop() as i32;
    data_stack.push((x > y) as u32);
}

// 0x4b
pub fn x_i32_gt_u(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    data_stack.push((x > y) as u32);
}

// 0x4c
pub fn x_i32_le_s(data_stack: &mut DataStack) {
    let y = data_stack.pop() as i32;
    let x = data_stack.pop() as i32;
    data_stack.push((x <= y) as u32);
}

// 0x4d
pub fn x_i32_le_u(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    data_stack.push((x <= y) as u32);
}

// 0x4e
pub fn x_i32_ge_s(data_stack: &mut DataStack) {
    let y = data_stack.pop() as i32;
    let x = data_stack.pop() as i32;
    data_stack.push((x >= y) as u32);
}

// 0x4f
pub fn x_i32_ge_u(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    data_stack.push((x >= y) as u32);
}

//
// BIT COUNTING OPERATIONS
//

// 0x67
pub fn x_i32_clz(data_stack: &mut DataStack) {
    let x = data_stack.pop();
    let mut cnt: u32 = 0;
    let mut mask = 0x80_00_00_00;
    while (x & mask) == 0 {
        cnt += 1;
        if mask == 1 {
            break;
        }
        mask >>= 1;
    }
    data_stack.push(cnt);
}

// 0x68
pub fn x_i32_ctz(data_stack: &mut DataStack) {
    let x = data_stack.pop();
    let mut cnt: u32 = 0;
    let mut mask = 1_u32;
    while (x & mask) == 0 {
        cnt += 1;
        if mask == 0x80_00_00_00 {
            break;
        }
        mask <<= 1;
    }
    data_stack.push(cnt);
}

// 0x69
pub fn x_i32_popcnt(data_stack: &mut DataStack) {
    let x = data_stack.pop();
    let mut cnt: u32 = 0;
    let mut mask = 0x80_00_00_00_u32;
    while mask > 0 {
        if (x & mask) != 0 {
            cnt += 1;
        }
        mask >>= 1;
    }
    data_stack.push(cnt);
}

//
// ARITHMETIC OPERATIONS
//

// 0x6a
pub fn x_i32_add(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    data_stack.push(x + y);
}

// 0x6b
pub fn x_i32_sub(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    data_stack.push(x - y);
}

// 0x6c
pub fn x_i32_mul(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    data_stack.push(x * y);
}

// 0x6d
pub fn x_i32_div_s(data_stack: &mut DataStack) {
    let y = data_stack.pop() as i32;
    let x = data_stack.pop() as i32;
    if y == 0 {
        // TODO: Make a proper error handling.
        // TODO: Make it a TRAP.
        panic!("Division by zero");
    }
    data_stack.push((x / y) as u32);
}

// 0x6e
pub fn x_i32_div_u(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    if y == 0 {
        // TODO: Make a proper error handling.
        // TODO: Make it a TRAP.
        panic!("Division by zero");
    }
    data_stack.push(x / y);
}

// 0x6f
pub fn x_i32_rem_s(data_stack: &mut DataStack) {
    let y = data_stack.pop() as i32;
    let x = data_stack.pop() as i32;
    if y == 0 {
        // TODO: Make a proper error handling.
        // TODO: Make it a TRAP.
        panic!("Division by zero");
    }
    data_stack.push((x % y) as u32);
}

// 0x70
pub fn x_i32_rem_u(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    if y == 0 {
        // TODO: Make a proper error handling.
        // TODO: Make it a TRAP.
        panic!("Division by zero");
    }
    data_stack.push(x % y);
}

//
// LOGICAL BIT OPERATIONS
//

// 0x71
pub fn x_i32_and(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    data_stack.push(x & y);
}

// 0x72
pub fn x_i32_or(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    data_stack.push(x | y);
}

// 0x73
pub fn x_i32_xor(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    data_stack.push(x ^ y);
}

// 0x74
pub fn x_i32_shl(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    data_stack.push(x << y);
}

// 0x75
pub fn x_i32_shr_s(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    data_stack.push(((x as i32) >> y) as u32);
}

// 0x76
pub fn x_i32_shr_u(data_stack: &mut DataStack) {
    let y = data_stack.pop();
    let x = data_stack.pop();
    data_stack.push(x >> y);
}

// 0x77
pub fn x_i32_rotl(_data_stack: &mut DataStack) {
    unimplemented!();
    /*
     *let y: data_stack.pop();
     *let x: data_stack.pop();
     *data_stack.push(x >> y);
     */
}

// 0x78
pub fn x_i32_rotr(_data_stack: &mut DataStack) {
    unimplemented!();
    /*
     *let y: data_stack.pop();
     *let x: data_stack.pop();
     *data_stack.push(x >> y);
     */
}

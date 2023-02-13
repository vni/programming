use rand::Rng;

/*
unsigned char chip8_fontset[80] =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};
*/

struct Chip8 {
    regs: [u8; 16],
    index: u16,
    pc: u16,
    sp: u8,
    stack: [u16; 16], //??32
    sound_timer: u8,  // buzzes while activated. Decreases at 60Hz. When 0 -> deactivates.
    delay_timer: u8,  // decreases till 0 at rate of 60Hz. When it 0 -> stops.
    frame_buffer: [u64; 32],
    memory: [u8; 4096],
}

fn draw_frame_buffer(chip: &Chip8) {
    for row in 0..32 {
        for col in (0..64).rev() {
            if chip.frame_buffer[row] & (1 << col) != 0 {
                print!("##");
            } else {
                print!("  ");
            }
        }
        println!();
    }
}

fn nnn(a: u8, b: u8, c: u8) -> u16 {
    (a as u16) << 8 | (b as u16) << 4 | (c as u16)
}

fn addr(a: u8, b: u8, c: u8) -> u16 {
    nnn(a, b, c)
}

fn kk(a: u8, b: u8) -> u8 {
    (a << 4) | b
}

fn byte(a: u8, b: u8) -> u8 {
    kk(a, b)
}

fn key_pressed(_key: u8) -> bool {
    unimplemented!();
}

fn wait_key_press() -> u8 {
    unimplemented!();
}

// FIXME: Add 60Hz timer.

fn trace(s: &str) {
    println!("{s}");
}

fn print_state(chip: &Chip8) {
    print!("REGS:");
    for r in chip.regs {
        print!(" {:04x}", r);
    }
    println!();
    println!("index_register: {:04x}", chip.index);
    println!("program_counter: {:04x}", chip.pc);
    println!("stack_pointer: {:02x}", chip.sp);
}

fn main() {
    let mut rng = rand::thread_rng();

    let mut chip: Chip8 = unsafe { std::mem::MaybeUninit::zeroed().assume_init() };

    //draw_frame_buffer(&chip);

    let args: Vec<String> = std::env::args().collect();
    if args.len() != 2 {
        panic!("Expect 1 argument: a rom filename to run");
    }

    let rom: Vec<u8> = std::fs::read(&args[1]).expect("failed to read rom file");
    if rom.len() % 2 == 1 {
        panic!("The rom.len() ({}) is not even", rom.len());
    }
    for (i, v) in rom.iter().enumerate() {
        if (i % 8) == 0 {
            print!("0x{:06x}:", i);
        }

        print!(" {:02x}", v);
        chip.memory[0x200 + i] = *v;

        if ((i + 1) % 8) == 0 {
            println!();
        }
    }
    println!();
    println!();
    println!();

    chip.pc = 0x200;

    loop {
        /*
        if chip.pc as usize >= opcodes.len() {
            panic!("program counter exceeded the program");
        }
        */

        /*
        let op: u16 = opcodes[chip.pc as usize];
        */
        let op: u16 = (chip.memory[chip.pc as usize] as u16) << 8
            | chip.memory[(chip.pc + 1) as usize] as u16;
        chip.pc += 2;

        println!("op: {:04x}", op);
        println!("===========================================================");
        print_state(&chip);
        println!();
        println!();
        println!();

        let a: u8 = ((op & 0xf000) >> 12) as u8;
        let b: u8 = ((op & 0x0f00) >> 8) as u8;
        let c: u8 = ((op & 0x00f0) >> 4) as u8;
        let d: u8 = (op & 0x000f) as u8;

        match (a, b, c, d) {
            // CLS: clear the display
            (0, 0, 0xE, 0) => {
                chip.frame_buffer = [0u64; 32];
            }
            // RET: return
            (0, 0, 0xE, 0xE) => {
                chip.pc = chip.stack[chip.sp as usize];
                chip.sp -= 1; // FIXME: check for underflow
            }
            // SYS addr;  obsolete
            (0, _, _, _) => unimplemented!("`SYS addr` instruction is obsolete"),
            //jump NNN,
            (1, a, b, c) => {
                chip.pc = addr(a, b, c);
            }
            //call NNN
            (2, a, b, c) => {
                chip.sp += 1;
                chip.stack[chip.sp as usize] = chip.pc;
                chip.pc = addr(a, b, c);
            }
            //SE Vx, byte; if vx == kk => skip next instruction
            (3, x, a, b) => {
                if chip.regs[x as usize] == byte(a, b) {
                    chip.pc += 2;
                }
            }
            //SNE Vx, byte; if vx != kk => skip next instruction
            (4, x, a, b) => {
                if chip.regs[x as usize] != byte(a, b) {
                    chip.pc += 2;
                }
            }
            //SE Vx, Vy;  0x5XY0 => if vx != vy => skip next instruction
            (5, x, y, 0) => {
                if chip.regs[x as usize] == chip.regs[y as usize] {
                    chip.pc += 2;
                }
            }
            // LD Vx, byte;  0x6XNN => vx := NN, //mov imm
            (6, x, a, b) => {
                chip.regs[x as usize] = byte(a, b);
            }
            // ADD Vx, byte;  0x7XNN => vx += NN, //ADD Vx, byte
            (7, x, a, b) => {
                chip.regs[x as usize] += byte(a, b);
            }
            // LD Vx, Vy;  0x8XY0 => vx := vy, //copy?, mov
            (8, x, y, 0) => {
                chip.regs[x as usize] = chip.regs[y as usize];
            }
            // OR Vx, Vy;  0x8XY1 => vx |= vy, //bit OR
            (8, x, y, 1) => {
                chip.regs[x as usize] |= chip.regs[y as usize];
            }
            // AND Vx, Vy;  0x8XY2 => vx &= vy, //bit AND
            (8, x, y, 2) => {
                chip.regs[x as usize] &= chip.regs[y as usize];
            }
            // XOR Vx, Vy;  0x8XY3 => vx ^= vy, //bit XOR
            (8, x, y, 3) => {
                chip.regs[x as usize] ^= chip.regs[y as usize];
            }
            // ADD Vx, Vy;  0x8XY4 => vx += vy, vf := CARRY BIT
            (8, x, y, 4) => {
                let result: u16 = chip.regs[x as usize] as u16 + chip.regs[y as usize] as u16;
                chip.regs[x as usize] = (result & 0x00ff) as u8;
                if result > 0xff {
                    chip.regs[0xf_usize] = 1;
                } else {
                    chip.regs[0xf_usize] = 0;
                }
            }
            // SUB Vx, By;  0x8XY5 => vx -= vy, vf := NOT BORROW BIT
            (8, x, y, 5) => {
                if chip.regs[x as usize] < chip.regs[y as usize] {
                    chip.regs[0xf_usize] = 0;
                } else {
                    chip.regs[0xf_usize] = 1;
                }

                chip.regs[x as usize] -= chip.regs[y as usize];
                // FIXME: address substraction with borrow.
            }
            // SHR Vx {, Vy};  0x8XY6 => vx >>= vy, vf := old least significant bit
            (8, x, _y, 6) => {
                chip.regs[0xf_usize] = chip.regs[x as usize] & 1;
                //chip.regs[x] >>= chip.regs[y];
                chip.regs[x as usize] >>= 1;
            }
            // SUBN Vx, Vy;  0x8XY7 => vx =- vy, vf := NOT BORROW BIT
            (8, x, y, 7) => {
                if chip.regs[y as usize] < chip.regs[x as usize] {
                    chip.regs[0xfusize] = 0;
                } else {
                    chip.regs[0xfusize] = 1;
                }

                chip.regs[x as usize] = chip.regs[y as usize] - chip.regs[x as usize];
                // FIXME: address substraction with borrow.
            }
            // SHL Vx {, Vy};  0x8XYE => vx <<= vy, vf := old most significant bit of Vx
            (8, x, _y, 0xe) => {
                chip.regs[0xfusize] = ((chip.regs[x as usize] as u16 & 0x8000) == 0x8000) as u8;
                //chip.regs[x] <<= chip.regs[y]
                chip.regs[x as usize] <<= 1;
            }
            // SNE Vx, Vy;  0x9XY0 => if vx != vy then skip next instruction,
            (9, x, y, 0) => {
                if chip.regs[x as usize] != chip.regs[y as usize] {
                    chip.pc += 2;
                }
            }
            // LD I, addr;  0xANNN => i := NNN, // assign to index 16bit register
            (0xa, a, b, c) => {
                chip.index = addr(a, b, c);
            }
            // JP V0, addr;  0xBNNN => jump0 NNN, // jump to address NNN + v0
            (0xb, a, b, c) => {
                chip.pc = chip.regs[0] as u16 + addr(a, b, c);
            }
            // RND Vx, byte;  0xCXNN => vx := random NN, // random number 0-255 AND NN
            (0xc, x, a, b) => {
                chip.regs[x as usize] = rng.gen::<u8>() & byte(a, b);
            }
            // DRW Vx, Vy, nibble;  0xDXYN => sprite vx vy N, //vf = 1 on collision
            (0xd, _x, _y, _n) => {
                unimplemented!();
            }
            // SKP Vx;  0xEX9E => if vx -key then, //is a key not pressed?
            (0xe, x, 9, 0xe) => {
                if key_pressed(chip.regs[x as usize]) {
                    chip.pc += 2;
                }
            }
            // SKNP Vx;  0xEXA1 => if vx key then, //is a key pressed?
            (0xe, x, 0xa, 1) => {
                if !key_pressed(chip.regs[x as usize]) {
                    chip.pc += 2;
                }
            }
            // LD Vx, DT;  0xFX07 => vx := delay
            (0xf, x, 0, 7) => {
                chip.regs[x as usize] = chip.delay_timer;
            }
            // LD Vx, K;  0xFX0A => vx := key, //wait for a keypress
            (0xf, x, 0, 0xa) => {
                chip.regs[x as usize] = wait_key_press();
            }
            // LD DT, Vx;  0xFX15 => delay := vx,
            (0xf, x, 1, 5) => {
                chip.delay_timer = chip.regs[x as usize];
            }
            // LD ST, Vx;  0xFX18 => buzzer := vx,
            (0xf, x, 1, 8) => {
                chip.sound_timer = chip.regs[x as usize];
            }
            // ADD I, Vx;  0xFX1E => i += vx, //index += vx
            (0xf, x, 1, 0xe) => {
                chip.index += chip.regs[x as usize] as u16;
            }
            // LD F, Vx;  0xFX29 => i := hex vx, //set i to a hex character
            (0xf, _x, 2, 9) => {
                unimplemented!();
            }
            // LD B, Vx;  0xFX33 => bcd vx, //decode vx into binary-coded decimal
            (0xf, x, 3, 3) => {
                let hundreds = chip.regs[x as usize] / 100;
                let tens = (chip.regs[x as usize] % 100) / 10;
                let ones = chip.regs[x as usize] % 10;

                chip.memory[chip.index as usize] = hundreds;
                chip.memory[(chip.index + 1) as usize] = tens;
                chip.memory[(chip.index + 2) as usize] = ones;
            }
            // LD [I], Vx;  0xFX55 => save vx, //save v0-vx to i through (i+x)
            (0xf, x, 5, 5) => {
                for i in 0..=x {
                    chip.memory[(chip.index + i as u16) as usize] = chip.regs[i as usize];
                }
                chip.index += (x + 1) as u16;
            }
            // LD Vx, [I];  0xFX65 => load vx, //load v0-vx from i through (i+x)
            (0xf, x, 6, 5) => {
                for i in 0..=x {
                    chip.regs[i as usize] = chip.memory[(chip.index + i as u16) as usize];
                }
                chip.index += (x + 1) as u16;
            }
            _ => panic!("unimplemented: {}", op),
        }
    }
    //println!("Finished");
}

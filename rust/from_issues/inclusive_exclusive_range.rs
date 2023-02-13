#[inline(never)]
#[no_mangle]
fn triangle_exc(n: u64) -> u64 {
    let mut count = 0;
    for j in (0..n + 1) {
        count += j;
    }
    count
}

#[inline(never)]
#[no_mangle]
fn triangle_inc(n: u64) -> u64 {
    let mut count = 0;
    for j in (0..=n) {
        count += j;
    }
    count
}

fn main() {
    let n: u64 = std::env::args().nth(1).unwrap().parse().unwrap();
    let what: u32 = std::env::args().nth(2).unwrap().parse().unwrap();

    match what {
        1 => println!("exc: {}", triangle_exc(n)),
        2 => println!("inc: {}", triangle_inc(n)),
        _ => panic!(),
    }
}

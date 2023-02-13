mod lib;

fn main() {
    let buf = lib::create_buffer(10);
    println!("buf.len: {}", buf.len());
    println!("are all zeroes?: {}", buf.iter().all(|&v| v == 0));

    let fib = lib::fibonacci();
    println!("fib: {:?}", fib);
    for win in fib.windows(3) {
        println!("win: {:?}", win);
        if win[0] + win[1] != win[2] {
            panic!("win[0] + win[1] SHOULD == win[2]");
        }
    }
}

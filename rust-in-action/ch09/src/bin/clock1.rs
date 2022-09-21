use chrono::{DateTime};
use chrono::{Local};
use clap::{Arg, App};

struct Clock;

impl Clock {
    fn get() -> DateTime<Local> {
        Local::now()
    }

    fn set() -> ! {
        unimplemented!()
    }
}

fn main() {
    // let clock = Clock{};
    // println!("clock::get(): {}", clock::get());
    // this is an associated function, not a method
    // help: use associated function syntax instead: `Clock::get`

    let app = App::new("clock")
        .version("0.1")
        .about("Gets and (aspirationally) sets the time.")
        .arg(
            Arg::with_name("action")
                .takes_value(true)
                .possible_values(&["get", "set"])
                .default_value("get"),
        )
        .arg(
            Arg::with_name("std")
                .short("s")
                .long("standard")
                .takes_value(true)
                .possible_values(&[
                              "rfc2822",
                              "rfc3339",
                              "timestamp",
                ])
                .default_value("rfc3339"),
        )
        .arg(
            Arg::with_name("datetime")
                .help("When <action> is 'set', apply <datetime>. \
                       Otherwise, ignore.",),
        );

    let args = app.get_matches();
    let action = args.value_of("action").unwrap();
    let std = args.value_of("std").unwrap();


    if action == "set" {
        unimplemented!()
    }

    let now = Clock::get();
    match std {
        "timestamp" => println!("{}", now.timestamp()),
        "rfc2822"   => println!("{}", now.to_rfc2822()),
        "rfc3339"   => println!("{}", now.to_rfc3339()),
        _ => unreachable!(),
    }

    // println!("Clock::get(): {}", Clock::get());
    // let now = Local::now();
    // println!("{}", now);


}

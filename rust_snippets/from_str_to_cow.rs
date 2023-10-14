use std::borrow::Cow;
use std::thread;

#[derive(Debug)]
struct Token<'a>(Cow<'a, str>);

impl<'a> Token<'a> {
    fn new<T>(raw: T) -> Token<'a>
        where T: Into<Cow<'a, str>>
    {
        Token(raw.into())
    }
}

fn main() {
    let raw = String::from("abc");
    let token_owned = Token::new(raw);
    let token_static = Token::new("123");

    thread::spawn(move || {
        println!("token_owned: {:?}", token_owned);
        println!("token_static: {:?}", token_static);
    }).join().unwrap();

    println!("Trying to send a token with a non-'static ref will fail.");
    let raw = String::from("abc");
    let s = &raw[..];
    let token = Token::new(s);

    thread::scope(|scope| {
        scope.spawn(move || {
            println!("token: {:?}", token);
        });
    })
    // thread::spawn(move || {
    //     println!("token: {:?}", token);
    // }).join().unwrap();
}
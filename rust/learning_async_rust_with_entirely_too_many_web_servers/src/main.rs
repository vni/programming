use std::io::{self, Read, Write};
use std::net::{TcpListener, TcpStream};

fn main() {
    let listener = TcpListener::bind("localhost:3000").unwrap();
    let mut connection_counter = 0;
    loop {
        let (connection, _) = listener.accept().unwrap();
        println!(
            "main> new connection> connection_counter: {}",
            connection_counter
        );

        std::thread::spawn(|| {
            if let Err(e) = handle_connection(connection) {
                println!("failed to handle connection: {e}")
            }
        });

        connection_counter += 1;
    }
}

fn handle_connection(mut connection: TcpStream) -> io::Result<()> {
    println!(">> got new connection from {:?}", connection);

    let mut read = 0;
    let mut request_buf = [0u8; 1024];

    loop {
        let num_bytes = connection.read(&mut request_buf[read..])?;
        if num_bytes == 0 {
            println!(">> client disconnected unexpectedly");
            break;
        }

        print!(
            "{:>4}: {}",
            read,
            std::str::from_utf8(&request_buf[read..read + num_bytes]).unwrap()
        );

        if request_buf.get(read + num_bytes - 4..read + num_bytes) == Some(b"\r\n\r\n") {
            println!("***YEEESSSS*** \\r\\n\\r\\n");
            break;
        } else if request_buf.get(read..read + num_bytes) == Some(b"\n\n") {
            println!("\\n\\n received");
            break;
        } else if request_buf.get(read..read + num_bytes) == Some(b".bye\n") {
            println!(">> .bye received. closing connection.");
            break;
        }

        read += num_bytes;
    }

    let request = String::from_utf8_lossy(&request_buf[..read]);
    println!("{}", request);

    let response = concat!(
        "HTTP/1.1 200 OK\r\n",
        "Content-Lengh: 12\n",
        "Connection: close\r\n\r\n",
        "Hello world!\n"
    );

    let mut written = 0;
    loop {
        let num_bytes = connection.write(response[written..].as_bytes())?;

        if num_bytes == 0 {
            println!(">> client disconnected unexpectedly");
            break;
        }

        println!(
            "wrote: {}",
            std::str::from_utf8(response[written..written + num_bytes].as_bytes()).unwrap()
        );

        written += num_bytes;

        if written == response.len() {
            break;
        }
    }

    connection.flush()

    // Ok(())
}

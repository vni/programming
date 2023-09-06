use epoll::{ControlOptions::*, Event, Events};
use std::collections::HashMap;
use std::io::{self, Read, Write};
use std::net::TcpListener;
use std::os::fd::AsRawFd;

enum ConnectionState {
    Read {
        request: [u8; 1024],
        read: usize,
    },
    Write {
        response: &'static [u8],
        written: usize,
    },
    Flush,
}

fn main() {
    let epoll = epoll::create(false).unwrap();

    let listener = TcpListener::bind("localhost:3000").unwrap();
    listener.set_nonblocking(true).unwrap();

    let event = Event::new(Events::EPOLLIN, listener.as_raw_fd() as _);
    epoll::ctl(epoll, EPOLL_CTL_ADD, listener.as_raw_fd(), event).unwrap();

    let mut connections = HashMap::new();
    let mut connection_counter = 0;

    loop {
        let mut events = [Event::new(Events::empty(), 0); 1024];
        // let timeout = -1;
        let n_events = epoll::wait(epoll, 0 /* timeout */, &mut events).unwrap();
        let mut completed = Vec::new();

        'next: for event in &events[..n_events] {
            let fd = event.data as i32;

            if fd == listener.as_raw_fd() {
                match listener.accept() {
                    Ok((connection, _)) => {
                        connection.set_nonblocking(true).unwrap();
                        let fd = connection.as_raw_fd();

                        let event = Event::new(Events::EPOLLIN | Events::EPOLLOUT, fd as _);
                        epoll::ctl(epoll, EPOLL_CTL_ADD, fd, event).unwrap();

                        let state = ConnectionState::Read {
                            request: [0u8; 1024],
                            read: 0,
                        };

                        connections.insert(fd, (connection, state));

                        println!(
                            "main> new connection> connection_counter: {}",
                            connection_counter
                        );
                        connection_counter += 1;
                    }
                    Err(e) if e.kind() == io::ErrorKind::WouldBlock => {
                        // std::thread::sleep(std::time::Duration::from_millis(100));
                        // continue;
                    }
                    Err(e) => panic!("{e}"),
                }

                continue 'next;
            }

            let (connection, state) = connections.get_mut(&fd).unwrap();

            if let ConnectionState::Read { request, read } = state {
                loop {
                    match connection.read(&mut request[*read..]) {
                        Ok(0) => {
                            println!("client disconnected unexpectedly");
                            completed.push(fd);
                            continue 'next;
                        }
                        Ok(n) => *read += n,
                        Err(e) if e.kind() == io::ErrorKind::WouldBlock => {
                            continue 'next;
                        }
                        Err(e) => panic!("{e}"),
                    }

                    if request.get(*read - 4..*read) == Some(b"\r\n\r\n") {
                        break;
                    }
                }

                let request = String::from_utf8_lossy(&request[..*read]);
                println!("{request}");

                let response = concat!(
                    "HTTP/1.1 200 OK\r\n",
                    "Content-Length: 12\n",
                    "Connection: close\r\n\r\n",
                    "Hello world!"
                );

                *state = ConnectionState::Write {
                    response: response.as_bytes(),
                    written: 0,
                };
            }

            if let ConnectionState::Write { response, written } = state {
                loop {
                    match connection.write(&response[*written..]) {
                        Ok(0) => {
                            println!("client disconnected unexpectedly");
                            completed.push(fd);
                            continue 'next;
                        }
                        Ok(n) => {
                            *written += n;
                        }
                        Err(e) if e.kind() == io::ErrorKind::WouldBlock => {
                            continue 'next;
                        }
                        Err(e) => panic!("{e}"),
                    }

                    if *written == response.len() {
                        break;
                    }
                }

                *state = ConnectionState::Flush;
            }

            if let ConnectionState::Flush = state {
                match connection.flush() {
                    Ok(_) => {
                        completed.push(fd);
                    }
                    Err(e) if e.kind() == io::ErrorKind::WouldBlock => {
                        continue 'next;
                    }
                    Err(e) => panic!("{e}"),
                }
            }
        }

        for fd in &mut completed {
            let (connection, _state) = connections.remove(&fd).unwrap();
            drop(connection);
        }
    }
}

use minifb::*;
// use minifb::{Key, MouseButton, MouseMode, Scale, Window, WindowOptions};

fn main() {
    const WIDTH: usize = 640;
    const HEIGHT: usize = 480;

    let mut buffer: Vec<u32> = vec![0; WIDTH * HEIGHT];

    let mut window = match Window::new(
        "Mouse Draw - Press ESC to exit",
        WIDTH, HEIGHT,
        WindowOptions {
            scale: Scale::X2,
            ..WindowOptions::default()
        },
    ) {
        Ok(win) => win,
        Err(err) => {
            println!("Unable to create window {}", err);
            return;
        }
    };

    let (mut width, mut height) = (WIDTH, HEIGHT);

    while window.is_open() && !window.is_key_down(Key::Escape) {
        if let Some((x, y)) = window.get_mouse_pos(MouseMode::Discard) {
            let screen_pos = ((y as usize) * (width / 2)) + x as usize;

            if window.get_mouse_down(MouseButton::Left) {
                buffer[screen_pos] = 0x00ffffff;
            }

            if window.get_mouse_down(MouseButton::Right) {
                buffer[screen_pos] = 0;
            }
        }

        if let Some(scroll) = window.get_scroll_wheel() {
            println!("Scrolling {} - {}", scroll.0, scroll.1);
        }

        window
            .update_with_buffer(&buffer, width / 2, height / 2)
            .unwrap();
    }

}

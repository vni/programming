pub fn production_rate_per_hour(speed: u8) -> f64 {
    let res: f64 = speed as f64 * 221.0f64;
    match speed {
        0..=4 => res,
        5..=8 => res * 0.90f64,
        9..=10 => res * 0.77f64,
        _ => panic!("Speed should be in the range [0; 10]"),
    }
}

pub fn working_items_per_minute(speed: u8) -> u32 {
    production_rate_per_hour(speed) as u32 / 60
}

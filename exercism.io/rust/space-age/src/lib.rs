pub struct Duration(u64);
impl From<u64> for Duration {
    fn from(s: u64) -> Self {
        Duration(s)
    }
}

pub trait Planet {
    fn years_during(d: &Duration) -> f64;
}

macro_rules! planet_macro {
    ( $planet_name:ident, $divisor:expr ) => {
        pub struct $planet_name;
        impl Planet for $planet_name {
            fn years_during(d: &Duration) -> f64 {
                d.0 as f64 / $divisor / 31557600f64
            }
        }
    };
}

planet_macro!(Mercury, 0.2408467);
planet_macro!(Venus, 0.61519726);
planet_macro!(Earth, 1.0);
planet_macro!(Mars, 1.8808158);
planet_macro!(Jupiter, 11.862615);
planet_macro!(Saturn, 29.447498);
planet_macro!(Uranus, 84.016846);
planet_macro!(Neptune, 164.79132);

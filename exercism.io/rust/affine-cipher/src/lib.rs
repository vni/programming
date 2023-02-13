/// While the problem description indicates a return status of 1 should be returned on errors,
/// it is much more common to return a `Result`, so we provide an error type for the result here.
#[derive(Debug, Eq, PartialEq)]
pub enum AffineCipherError {
    NotCoprime(i32),
}

/// Encodes the plaintext using the affine cipher with key (`a`, `b`). Note that, rather than
/// returning a return code, the more common convention in Rust is to return a `Result`.
pub fn encode(plaintext: &str, a: i32, b: i32) -> Result<String, AffineCipherError> {
    Ok(plaintext
        .to_lowercase()
        .chars()
        .filter(|c| c.is_alphanumeric())
        .map(|c| {
            if c.is_alphabetic() {
                (a * (c as u8 - 'a' as u8) as i32 + b) % 26
            } else {
                c as i32
            }
        })
        .collect())
}

/// Decodes the ciphertext using the affine cipher with key (`a`, `b`). Note that, rather than
/// returning a return code, the more common convention in Rust is to return a `Result`.
pub fn decode(ciphertext: &str, a: i32, b: i32) -> Result<String, AffineCipherError> {
    unimplemented!("Decode {} with the key ({}, {})", ciphertext, a, b);
}

fn helper_func(mut vec: Vec<u8>) -> bool {
    if vec.len() < 2 {
        return false;
    }

    for (i, v) in vec.iter_mut().enumerate() {
        if i % 2 == 1 {
            *v *= 2;
            if *v > 9 {
                *v -= 9;
            }
        }
    }

    vec.iter().sum::<u8>() % 10 == 0
}

pub struct Luhn {
    is_valid: bool,
}

impl Luhn {
    pub fn is_valid(&self) -> bool {
        self.is_valid
    }
}

/// Here is the example of how the From trait could be implemented
/// for the &str type. Naturally, you can implement this trait
/// by hand for the every other type presented in the test suite,
/// but your solution will fail if a new type is presented.
/// Perhaps there exists a better solution for this problem?
impl<'a> From<&'a str> for Luhn {
    fn from(input: &'a str) -> Self {
        let b = input
            .chars()
            .filter(|c| !c.is_whitespace())
            .all(char::is_numeric);
        if b == false {
            return Self { is_valid: false };
        }

        let mut vec = Vec::<u8>::new();

        for c in input.chars().filter(|c| !c.is_whitespace()).rev() {
            vec.push(c.to_digit(10).unwrap() as u8);
        }

        Self {
            is_valid: helper_func(vec),
        }
    }
}

impl From<String> for Luhn {
    fn from(input: String) -> Self {
        Self::from(input.as_str())
    }
}

impl From<u8> for Luhn {
    fn from(input: u8) -> Self {
        Self::from(input as u64)
    }
}

impl From<u16> for Luhn {
    fn from(input: u16) -> Self {
        Self::from(input as u64)
    }
}

impl From<u32> for Luhn {
    fn from(input: u32) -> Self {
        Self::from(input as u64)
    }
}

impl From<u64> for Luhn {
    fn from(mut input: u64) -> Self {
        let mut vec = Vec::<u8>::new();
        while input > 0 {
            let d = (input % 10) as u8;
            input /= 10;

            vec.push(d);
        }

        Self {
            is_valid: helper_func(vec),
        }
    }
}

impl From<usize> for Luhn {
    fn from(input: usize) -> Self {
        Self::from(input as u64)
    }
}

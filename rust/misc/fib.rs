fn fib(n: u32) -> u32 {
    match n {
        0 => 0,
        1 => 1,
        n => fib(n-1) + fib(n-2),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn fib_0() {
        assert_eq!(fib(0), 0);
    }

    #[test]
    fn fib_1() {
        assert_eq!(fib(1), 1);
    }

    #[test]
    fn fib_5() {
        assert_eq!(fib(5), 5);
    }

    #[test]
    fn fib_7() {
        assert_eq!(fib(7), 13);
    }

    #[test]
    fn fib_many() {
        let expected = [0, 1, 1, 2, 3, 5, 8, 13, 21,
                        34, 55, 89, 144, 233, 377, 610,
                        987, 1597, 2584, 4181, 6765];
        for (i, &v) in expected.iter().enumerate() {
            assert_eq!(fib(i as u32), v);
        }
    }
}

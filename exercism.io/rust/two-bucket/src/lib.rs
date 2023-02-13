#[derive(PartialEq, Eq, Debug)]
pub enum Bucket {
    One,
    Two,
}

/// A struct to hold your results in.
#[derive(PartialEq, Eq, Debug)]
pub struct BucketStats {
    /// The total number of "moves" it should take to reach the desired number of liters, including
    /// the first fill.
    pub moves: u8,
    /// Which bucket should end up with the desired number of liters? (Either "one" or "two")
    pub goal_bucket: Bucket,
    /// How many liters are left in the other bucket?
    pub other_bucket: u8,
}

struct Buck {
    capacitry: u8,
    volume: u8,
}

fn x(b1: Buck, b2: Buck, moves: u8, goal: u8) -> Option<BucketStats> {}

/// Solve the bucket problem
pub fn solve(
    capacity_1: u8,
    capacity_2: u8,
    goal: u8,
    start_bucket: &Bucket,
) -> Option<BucketStats> {
    let mut moves = 1;

    if goal == capacity_1 || goal == capacity_2 {}

    unimplemented!(
        "Given one bucket of capacity {}, another of capacity {}, starting with {:?}, find pours to reach {}, or None if impossible",
        capacity_1,
        capacity_2,
        start_bucket,
        goal,
    );
}

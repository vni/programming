use std::collections::HashMap;
use std::sync::{Arc, Mutex};
use std::thread;

pub fn frequency(input: &[&str], worker_count: usize) -> HashMap<char, usize> {
    let mut hmap = HashMap::<char, usize>::new();

    let arc_mtx = Arc::new(Mutex::new(&mut hmap));

    //assert!(input.len() == worker_count || worker_count == 1);

    // let mut threads = Vec::with_capacity(worker_count);

    for arr in input {
        let arc_mtx_clone = Arc::clone(&arc_mtx);
        /*
        threads.push(thread::spawn(move || {
            for c in arr.to_lowercase().chars().filter(|c| c.is_alphabetic()) {
                let hmap = &mut *arc_mtx_clone.lock().unwrap();
                *hmap.entry(c).or_insert(0) += 1;
            }
        }));
        */
    }

    /*
    for t in threads {
        t.join().unwrap();
    }
    */

    hmap

    /*unimplemented!(
        "Count the frequency of letters in the given input '{:?}'. Ensure that you are using {} to process the input.",
        input,
        match worker_count {
            1 => "1 worker".to_string(),
            _ => format!("{} workers", worker_count),
        }
    );*/
}

fn traverse(dir: &str, prefix: &str) -> std::io::Result<()> {
    use std::fs;
    use std::path::Path;

    let p = Path::new(dir);

    // let fs::read_dir(dir).unwrap();
    let mut entries_iter = fs::read_dir(dir)?;
    let mut next = entries_iter.<F2>
    loop {
        if entries_iter.is_none() {
            break;
        }

        /*
        let next = entries_iter.next();
        entries_iter = next;
        if next.is_none() {
            break;
        }
        */
    }

    for p in fs::read_dir(dir)? {
        let p = p.unwrap();
        let name = p.file_name().into_string().unwrap();
        if p.file_type().unwrap().is_file() {
            println!("{}+-- {}", prefix, name);
        } else if p.file_type().unwrap().is_dir() {
            println!("{}+-- {}/", prefix, name);
            traverse(&format!("{}/{}", dir, name), &format!("{}|   ", prefix));
        }
    }

    Ok(())
}

fn main() {
    let args = std::env::args().collect::<Vec<String>>();
    traverse(".", "").unwrap();
}

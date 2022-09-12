use anyhow::Error;

/// While using `&[&str]` to handle flags is convenient for exercise purposes,
/// and resembles the output of [`std::env::args`], in real-world projects it is
/// both more convenient and more idiomatic to contain runtime configuration in
/// a dedicated struct. Therefore, we suggest that you do so in this exercise.
///
/// In the real world, it's common to use crates such as [`clap`] or
/// [`structopt`] to handle argument parsing, and of course doing so is
/// permitted in this exercise as well, though it may be somewhat overkill.
///
/// [`clap`]: https://crates.io/crates/clap
/// [`std::env::args`]: https://doc.rust-lang.org/std/env/fn.args.html
/// [`structopt`]: https://crates.io/crates/structopt
#[derive(Debug)]
pub struct Flags {
    line_numbers: bool,
    only_names: bool,
    case_insensitive: bool,
    invert: bool,
    entire_lines: bool,
}

impl Flags {
    pub fn new(flags: &[&str]) -> Self {
        let mut res = Self {
            line_numbers: false,
            only_names: false,
            case_insensitive: false,
            invert: false,
            entire_lines: false,
        };

        for f in flags {
            match f {
                &"-n" => res.line_numbers = true,
                &"-l" => res.only_names = true,
                &"-i" => res.case_insensitive = true,
                &"-v" => res.invert = true,
                &"-x" => res.entire_lines = true,
                _ => panic!("Unknown flag: {}", f),
            }
        }

        res
    }
}

pub fn grep(pattern: &str, flags: &Flags, files: &[&str]) -> Result<Vec<String>, Error> {
    use std::io::BufRead;

    let flag_multiple_files = if files.len() > 1 { true } else { false };

    let re = {
        let mut pattern: String = pattern.into();
        if flags.case_insensitive {
            pattern = pattern.to_lowercase();
        }

        if flags.entire_lines {
            pattern = format!("^{pattern}$");
        }

        regex::Regex::new(pattern.as_str())?
    };

    let mut res: Vec<String> = Vec::new();

    for filename in files {
        let file = std::fs::File::open(filename)?;
        for (lnum, line) in std::io::BufReader::new(file).lines().enumerate() {
            let line = line.unwrap();
            let match_against;
            if flags.case_insensitive {
                match_against = line.to_lowercase();
            } else {
                match_against = line.clone();
            }

            let is_match = if flags.invert {
                !re.is_match(match_against.as_str())
            } else {
                re.is_match(match_against.as_str())
            };

            if is_match {
                if flags.only_names {
                    res.push((**filename).into());
                    break;
                }

                let mut res_line = String::with_capacity(256);
                if flag_multiple_files {
                    res_line += format!("{}:", filename).as_str();
                }

                if flags.line_numbers {
                    res_line += format!("{}:", lnum + 1).as_str();
                }

                res_line += format!("{}", line).as_str();

                res.push(res_line);
            }
        }
    }

    Ok(res)
}

use std::fmt::Write;

use ed25519_dalek::{
    PublicKey,
    SecretKey,
    Keypair,
    Verifier,
    Signature,
    Signer,
    PUBLIC_KEY_LENGTH,
    SECRET_KEY_LENGTH,
    SIGNATURE_LENGTH,
    KEYPAIR_LENGTH,
};

pub struct CommandLineOptions {
    pub cmd: String,
    pub public_key: Option<PublicKey>,
    pub private_key: Option<SecretKey>,
    pub message: Option<String>,
    pub signature: Option<Signature>,
}

pub fn u8_to_string(a: &[u8]) -> String {
    let mut s = String::with_capacity(a.len() + 1);
    for v in a.iter() {
        write!(s, "{:02x}", v).unwrap();
    }
    s
}

pub fn parse_command_line_args() -> CommandLineOptions {
    let mut opts = CommandLineOptions {
        cmd: String::new(),
        public_key: None,
        private_key: None,
        message: None,
        signature: None,
    };

    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        panic!("At least 2 arguments expected");
    }

    opts.cmd = args[1].clone();

    let n = args.len();
    let mut i = 2;
    while i < n {
        if args[i] == "--public" {
            if i + 1 >= n {
                panic!("--public expects an argument which is missing");
            }

            let pubkey = args[i + 1].clone();
            let pubkey = hex::decode(pubkey).unwrap();
            let pubkey: PublicKey = PublicKey::from_bytes(&pubkey[..PUBLIC_KEY_LENGTH]).unwrap();
            opts.public_key = Some(pubkey);

            i += 2;
        } else if args[i] == "--private" {
            if i + 1 >= n {
                panic!("--private expects an argument which is missing");
            }

            let privkey = args[i + 1].clone();
            let privkey = hex::decode(privkey).unwrap();
            let privkey: SecretKey = SecretKey::from_bytes(&privkey[..SECRET_KEY_LENGTH]).unwrap();
            opts.private_key = Some(privkey);

            i += 2;
        } else if args[i] == "--message" {
            if i + 1 >= n {
                panic!("--message expects an argument which is missing");
            }

            let message = args[i + 1].to_string();
            opts.message = Some(message);

            i += 2;
        } else if args[i] == "--signature" {
            if i + 1 >= n {
                panic!("--signature expects an argument which is missing");
            }

            let signature = args[i + 1].clone();
            let signature = hex::decode(signature).unwrap();
            let signature: Signature = Signature::from_bytes(&signature[..64]).unwrap();
            opts.signature = Some(signature);

            i += 2;
        } else {
            panic!("Unexpected command line argument: {}", args[i]);
        }
    }

    opts
}

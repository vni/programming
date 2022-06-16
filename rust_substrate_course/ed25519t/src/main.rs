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

use sha2::{digest::Digest, Sha512};

struct CommandLineOptions {
    cmd: String,
    public_key: Option<PublicKey>,
    private_key: Option<SecretKey>,
    message: Option<String>,
    signature: Option<Signature>,
}

fn u8_to_string(a: &[u8]) -> String {
    let mut s = String::with_capacity(a.len() + 1);
    for v in a.iter() {
        write!(s, "{:02x}", v).unwrap();
    }
    s
}

fn parse_command_line_args() -> CommandLineOptions {
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

fn generate() {
    let mut rng = rand::rngs::OsRng;
    let keypair: Keypair = Keypair::generate(&mut rng);
    println!("public key:  {}", u8_to_string(&keypair.public.to_bytes()));
    println!("private key: {}", u8_to_string(&keypair.secret.to_bytes()));
}

fn sign(public: PublicKey, private: SecretKey, message: String) -> Signature {
    let keypair = Keypair { secret: private, public: public };
    let mut prehash: Sha512 = Sha512::default();
    prehash.update(message.as_bytes());

    let sig = keypair.sign_prehashed(prehash, None).unwrap();
    sig
}

fn verify(public: PublicKey, private: SecretKey, message: String, expected_signature: Signature) -> bool {
    let keypair = Keypair { secret: private, public: public };
    let mut prehash: Sha512 = Sha512::default();
    prehash.update(message.as_bytes());

    keypair.verify_prehashed(prehash, None, &expected_signature).is_ok()
}

fn main() {
    let options = parse_command_line_args();

    match options.cmd.as_str() {
        "generate" => {
            generate();
        }
        "sign" => {
            if options.private_key.is_none() {
                panic!("sign: No private key in the command line arguments");
            }

            if options.public_key.is_none() {
                panic!("sign: No public key in the command line arguments");
            }

            if options.message.is_none() {
                panic!("sign: No message in the command line arguments");
            }

            let signature = sign(options.public_key.unwrap(), options.private_key.unwrap(), options.message.unwrap());
            println!("signature: {}", u8_to_string(&signature.to_bytes()));
        }
        "verify" => {
            if options.private_key.is_none() {
                panic!("verify: No private key in the command line arguments");
            }

            if options.public_key.is_none() {
                panic!("verify: No public key in the command line arguments");
            }

            if options.message.is_none() {
                panic!("verify: No message in the command line arguments");
            }

            if options.signature.is_none() {
                panic!("verify: No signature in the command line arguments present");
            }

            let is_good = verify(options.public_key.unwrap(), options.private_key.unwrap(),
                                 options.message.unwrap(), options.signature.unwrap());
            println!("verify is_good: {}", is_good);
        }
        _ => panic!("Unknown command: {}", options.cmd),
    }
}

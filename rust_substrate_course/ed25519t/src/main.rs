mod utils;

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

fn generate() {
    let mut rng = rand::rngs::OsRng;
    let keypair: Keypair = Keypair::generate(&mut rng);
    println!("public key:  {}", utils::u8_to_string(&keypair.public.to_bytes()));
    println!("private key: {}", utils::u8_to_string(&keypair.secret.to_bytes()));
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
    let options = utils::parse_command_line_args();

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
            println!("signature: {}", utils::u8_to_string(&signature.to_bytes()));
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

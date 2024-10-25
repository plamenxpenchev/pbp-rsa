# pbp-rsa
**pbp-rsa (Pretty Bad Privacy)** is a project, which handles RSA key generation (1024, 2048, and 4096 bit sizes), plaintext files encryption and decryption. This is a playground crypto project, so I do not recommend using it for any serious crypto purposes. If you need something like that, I would direct you to PQC - consider Kyber and its alternatives.

## Table of Contents
- [Implementation](#implementation)
- [Docker setup](#docker-setup)
- [Usage](#usage)
- [Alice and Bob](#alice-and-bob)
- [License](#license)

## Implementation
- **Arbitrary precision arithmetic (GMP implementation)**
  - This project uses the GMP library (*The GNU
Multiple Precision Arithmetic Library*) for arbitrary precision arithmetic, in order to go beyond the supported C data types.
  - In the first version of version of pbp-rsa, primes generated were restricted to the 4th root of C's long long. In this way, exponentiation modulo N could reach at most the upper bound of the long long data type.
  - For proper security with PK cryptography, RSA in particular, key sizes of a much larger magnitude are necessary, as opposed to symmetric crypto algorithms. Hence the need for arbitrary precision arithmetic.

- **RSA key generation**
  - Prime generation of `p` and `q`.
    - Generate a CSPRNG random seed via stdlib's `arc4random`.
    - Feed the seed into a GMP `gmp_randstate_t` random state.
    - Generate a GMP arbitrary precision random number.
    - Find the next occuring prime starting from the random number:
      - Checking divisibility of consecutive numbers up to the square root of the potential prime is very computationally heavy when working with large key sizes. The calculations done in the first version of the project have given way to the usage of GMP's probabilistic `mpz_nextprime`.
    - When computing the two, the selected key size is taken into account, such that `N` is in the respective bounds.
  - Generating `e`, `d`, and `N`:
    - Generate a prime `e`.
    - Execute the Extended Euclidean Algorithm on `e` with the Euler Totient of `p` and `q` to verify invertibility of `e` in the ring of the Totient mod
      - The project's own recursive implementation of EEA `ext_eucl_rec_alg` has been deprecated in favor of GMP's `mpz_gcdext`. The EEA implementation can still be found under `/src/deprecated/math-utils`, but is no longer used.
    - `d` is derived as `e's` coefficient in the linear combination derived by EEA, when the GCD is 1.
      - In the case `d` is negative, its equivalence class in the ring of the Totient is used.
    - `N` is `p` times `q`.

## Docker setup
- Run `bash docker-build.sh` to build the GCC docker image, configuring and installing the GMP and BSD libraries and setting up the project executable.
- Run `bash docker-run.sh` to run the project executable docker container.
- Alternatively, to compile and run locally:
  - Needed libraries: GMP, BSD.
  - GCC: `` gcc src/*.c src/*/*.c -o exec/pbp-rsa -lbsd -lm -lgmp `pkg-config --libs libbsd` `` from the project root.
  - Run `` ./exec/pbp-rsa `` from the project root.

## Usage
- Generate a pair of RSA public and private keys (`rsa.pub` and `rsa` respectively, found under `/exec/keys/`).
- Share `rsa.pub` with a friend. 
- Text files produced will be stored under `/exec/text-files`.

## Alice and Bob

### Key creation and key exchange

- `bash docker-run.sh bob`
- (Bob) Pick menu option 1 (`Generate RSA key pair`), then option 3 (`4096 bit size`)
- `docker cp pbp-rsa-bob://usr/src/pbp-rsa/exec/keys/rsa.pub ./bob.pub`

- `bash docker-run.sh alice`
- (Alice) Pick menu option 1 (`Generate RSA key pair`), then option 3 (`4096 bit size`)
- `docker cp ./bob.pub pbp-rsa-alice://usr/src/pbp-rsa/exec/keys/`

### Message creation and encryption

- `docker exec -it pbp-rsa-alice bash -c "echo Hello Bob! >> /usr/src/pbp-rsa/exec/text-files/plaintext_message.txt"`
- (Alice) Pick menu option 2 (`Encipher text file`)
- (Alice) When prompted with `Enter the path to the 'rsa.pub' file of the person you wish to send a message to` enter:
  - `/usr/src/pbp-rsa/exec/keys/bob.pub`
- (Alice) When prompted with `Enter the path to the file you wish to encrypt` enter:
  - `/usr/src/pbp-rsa/exec/text-files/plaintext_message.txt`

### Message transfer and decryption

- `docker cp pbp-rsa-alice://usr/src/pbp-rsa/exec/text-files/cipher_text.txt ./encrypted_message.txt`
- `docker cp ./encrypted_message.txt pbp-rsa-bob://usr/src/pbp-rsa/exec/text-files/`
- (Bob) Pick menu option 3 (`Decipher text file`)
- (Bob) When prompted with `Enter the path to the file you wish to decrypt` enter:
  - `/usr/src/pbp-rsa/exec/text-files/encrypted_message.txt`
- The `Hello Bob!` message will be printed.


## License
This project is licensed under the [Apache License](LICENSE).

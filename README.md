# pbp-rsa
**Pretty Bad Privacy (pbp-rsa)** is a project, which handles RSA key generation, text files encryption and decryption.

- **RSA key generation**
  - Prime generation of `p` and `q`
    - Generate CSPRNG random numbers via stdlib's `arc4random`
      - Upper bound - the 4th root of C's signed long long upper bound
    - Use PNT to derive bounds of a prime occuring around CSPRNG random number
    - Check primality of members of derived interval
  - Generating `e`, `d`, and `N`
    - Generate a prime `e`
    - Execute the Extended Euclidean Algorithm on `e` with the Euler Totient of `p` and `q` to verify invertibility of `e` in the ring of the Totient mod
      - The EEA is executed in a recursive implementation, making use of the algorithm's generalizable steps
    - `d` is derived as `e's` coefficient in the linear combination derived by EEA, when the GCD is 1
      - In the case `d` is negative, its equivalence class in the ring of the Totient is used
    - `N` is `p` times `q`

- **RSA cipher**
  - Use distributivity of mod under multiplication
  - Reduce exponentiation rounds
    - Implement a square-and-multiply algorithm
      - Bitwise conversion of exponents (`e` and `d`)

- **Project compilation**
  - To compile the project, execute `` gcc -lbsd -o ../exec/rsa-cipher *.c */*.c -lm `pkg-config --libs libbsd` `` inside the `src` folder
  - A compiled `rsa-cipher` executable is included in the project under `exec`
  
- **Usage**
  - Generate a pair of RSA public and private keys (`rsa.pub` and `rsa` respectively, found under `exec/keys/`)
  - Share `rsa.pub` with a friend
  - Text files produced will be stored under `exec/text-files`
  - Encipher and decipher at will :)

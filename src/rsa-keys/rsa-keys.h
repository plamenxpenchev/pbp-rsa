void gen_rsa_keys(mpz_t e, mpz_t d, mpz_t N, unsigned long int rsa_key_bit_size);
void save_rsa_keys(mpz_t e, mpz_t d, mpz_t N);
void get_rsa_pub_keys(mpz_t e, mpz_t N);
void get_rsa_priv_keys(mpz_t d, mpz_t N);

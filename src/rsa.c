#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "./rsa-keys/rsa-keys.h"
#include "./io-utils/io-utils.h"

void rsa(mpz_t pre_cipher_val, mpz_t post_cipher_val, mpz_t rsa_exp_key, mpz_t N)
{
  // post_cipher_val = (pre_cipher_val^rsa_exp_key) mod N
  mpz_powm(post_cipher_val, pre_cipher_val, rsa_exp_key, N);
}

int rsa_encipher()
{
  const int DECIMAL_BASE = 10;

  mpz_t e;
  mpz_t N;
  mpz_t plain_text_val;
  mpz_t cipher_text_val;

  mpz_init(e);
  mpz_init(N);
  mpz_init(plain_text_val);
  mpz_init(cipher_text_val);

  char *z_cipher_val;

  get_rsa_pub_keys(e, N);

  int pltxt_ascii_char;

  FILE *plain_fp;
  FILE *cipher_fp;

  plain_fp = get_file_to_encrypt();
  cipher_fp = fopen("text-files/cipher_text.txt","w");

  printf("\nEncipher start...\n");

  while(1) {

     pltxt_ascii_char = fgetc(plain_fp);

     if(feof(plain_fp)) {
        break ;
     }

     mpz_set_ui(plain_text_val, (unsigned long int) pltxt_ascii_char);

     rsa(plain_text_val, cipher_text_val, e, N);
     z_cipher_val = mpz_get_str(NULL, DECIMAL_BASE, cipher_text_val);
     fprintf(cipher_fp, "%s\n", z_cipher_val);
  }

  mpz_clear(e);
  mpz_clear(N);
  mpz_clear(plain_text_val);
  mpz_clear(cipher_text_val);

  free(z_cipher_val);
  z_cipher_val = NULL;

  fclose(plain_fp);
  fclose(cipher_fp);

  return 0;
}

int rsa_decipher()
{
  mpz_t d;
  mpz_t N;
  mpz_t plain_text_val;
  mpz_t cipher_text_val;

  mpz_init(d);
  mpz_init(N);
  mpz_init(plain_text_val);
  mpz_init(cipher_text_val);

  unsigned long int z_plain_val;

  get_rsa_priv_keys(d, N);

  long long int decipher_ascii_char;

  FILE *cipher_fp;
  FILE *decipher_fp;

  cipher_fp = get_file_to_decrypt();
  decipher_fp = fopen("text-files/deciphered_text.txt","w");

  int read_gmp_z_exit_code;

  printf("\nDecipher start...\n");
  printf("The deciphered text is:\n\n");
  while(1) {

    read_gmp_z_exit_code = read_gmp_z(cipher_text_val, cipher_fp);

    if (read_gmp_z_exit_code == 3) {
      printf("\n---EOF---\n");
      break;
    }

    rsa(cipher_text_val, plain_text_val, d, N);
    z_plain_val = mpz_get_ui(plain_text_val);
    printf("%c", (int) z_plain_val);
    fprintf(decipher_fp,"%c", (int) z_plain_val);
  }

  mpz_clear(d);
  mpz_clear(N);
  mpz_clear(plain_text_val);
  mpz_clear(cipher_text_val);

  fclose(cipher_fp);
  fclose(decipher_fp);

  return 0;
}

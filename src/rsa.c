#include <stdio.h>
#include <stdlib.h>
#include "./io-utils/io-utils.h"
#include "./math-utils/math-utils.h"
#include "./rsa-keys/rsa-keys.h"

long long int rsa (long long int orig_val, long long int rsa_exp_key, long long int N) {
  long long int powers_of_two[100];
  int bit_pos = gen_powers_of_two(powers_of_two, rsa_exp_key);

  int *bitwise_rep_exp;
  bitwise_rep_exp = (int *) malloc((bit_pos + 1 ) * sizeof(int));
  gen_exp_bitwise_rep(rsa_exp_key, bit_pos, bitwise_rep_exp, powers_of_two);

  long long int post_cipher_val = orig_val;
  for (bit_pos--; bit_pos >= 0; bit_pos--){

    post_cipher_val = mod_lli(post_cipher_val, N);
    post_cipher_val = post_cipher_val * post_cipher_val;
    post_cipher_val = mod_lli(post_cipher_val, N);

    int bit = bitwise_rep_exp[bit_pos];
    if (bit == 1) {
      post_cipher_val = post_cipher_val * orig_val;
      post_cipher_val = mod_lli(post_cipher_val, N);
    }
  }

  free(bitwise_rep_exp);
  bitwise_rep_exp = NULL;

  return post_cipher_val;
}

int rsa_encipher() {
  struct rsa_pub_keys rsa_pub_keys = get_rsa_pub_keys();

  int pltxt_ascii_char;
  long long int cipher_text_val;

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

     cipher_text_val = rsa ((long long int) pltxt_ascii_char, rsa_pub_keys.e, rsa_pub_keys.N);
     fprintf(cipher_fp, "%lli\n", cipher_text_val);
  }

  fclose(plain_fp);
  fclose(cipher_fp);

  return 0;
}

int rsa_decipher() {
  struct rsa_priv_keys rsa_priv_keys = get_rsa_priv_keys();

  long long int cipher_text_val;
  long long int decipher_ascii_char;

  FILE *cipher_fp;
  FILE *decipher_fp;

  cipher_fp = get_file_to_decrypt();
  decipher_fp = fopen("text-files/deciphered_text.txt","w");

  int read_lli_status_code;

  printf("\nDecipher start...\n");
  printf("The deciphered text is:\n\n");
  while(1) {

    read_lli_status_code = read_lli(&cipher_text_val, cipher_fp);

    if (read_lli_status_code == 3) {
      printf("\n---EOF---\n");
      break;
    }

    decipher_ascii_char = rsa (cipher_text_val, rsa_priv_keys.d, rsa_priv_keys.N);
    printf("%c", (int) decipher_ascii_char);
    fprintf(decipher_fp,"%c", (int) decipher_ascii_char);
  }

  fclose(cipher_fp);
  fclose(decipher_fp);

  return 0;
}

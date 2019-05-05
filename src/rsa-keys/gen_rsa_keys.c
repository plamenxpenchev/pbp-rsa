#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "../rand-num-utils/rand-num-utils.h"

void gen_rsa_keys(mpz_t e, mpz_t d, mpz_t N, unsigned long int rsa_key_bit_size)
{
  // Initialize random number
	mpz_t rand_num;
	mpz_init(rand_num);

  mp_bitcnt_t bit_size = (mp_bitcnt_t) rsa_key_bit_size;

  // Initialize key_upper_bound = 1
  mpz_t key_upper_bound;
  mpz_init(key_upper_bound);
  mpz_set_ui(key_upper_bound, 1);

  // key_upper_bound = key_upper_bound * 2^(bit_size)
  mpz_mul_2exp(key_upper_bound, key_upper_bound, bit_size);

  gen_random_number(rand_num, rsa_key_bit_size);

  mpz_t rand_num_quot;
  mpz_init(rand_num_quot);

  // Calculate the quotient in the division
  mpz_tdiv_q(rand_num_quot, key_upper_bound, rand_num);

  mpz_t p;
  mpz_t q;
	mpz_t p_less_1;
	mpz_t q_less_1;

  mpz_init(p);
  mpz_init(q);
	mpz_init(p_less_1);
	mpz_init(q_less_1);

  mpz_nextprime(p, rand_num);
  mpz_nextprime(q, rand_num_quot);
	mpz_sub_ui(p_less_1, p, 1);
	mpz_sub_ui(q_less_1, q, 1);

	mpz_t euler_totient;
	mpz_t euler_totient_coeff;
	mpz_t gcd;

	mpz_init(euler_totient);
	mpz_init(euler_totient_coeff);
	mpz_init(gcd);

	mpz_mul(N, p, q);
	mpz_mul(euler_totient, p_less_1, q_less_1);

	do {
		do {

			gen_random_number(e, rsa_key_bit_size);
			mpz_nextprime(e, e);
		} while (mpz_cmp(e, euler_totient) >= 0);

		// gcd = euler_totient*euler_totient_coeff + e*d
		mpz_gcdext(gcd, euler_totient_coeff, d, euler_totient, e);
	} while (mpz_cmp_ui(gcd, 1) != 0);

  // Get d's equivalence class in the ring of the Totient mod
	if (mpz_cmp_ui(d, 0) < 0) {
		mpz_add(d, d, euler_totient);
	}

  // Garbage collection
  mpz_clear(rand_num);
  mpz_clear(rand_num_quot);
  mpz_clear(key_upper_bound);

  mpz_clear(p);
  mpz_clear(q);
  mpz_clear(p_less_1);
  mpz_clear(q_less_1);

  mpz_clear(euler_totient);
  mpz_clear(euler_totient_coeff);
  mpz_clear(gcd);
}

#include <stdio.h>
#include <stdlib.h>
#include <bsd/stdlib.h>
#include <gmp.h>

void gen_random_number(mpz_t random_num, unsigned long int max_bit_size)
{
  // Initialize random seed
  // uint32_t arc4random(void);
  unsigned long int random_seed;
  random_seed = arc4random();

  // Initialize random state
  gmp_randstate_t random_state;
  gmp_randinit_default(random_state);
  gmp_randseed_ui(random_state, random_seed);

  // Prepare random bit size upper bound
  mpz_t bit_size_bound;
  mpz_init(bit_size_bound);
  mpz_set_ui(bit_size_bound, max_bit_size);
  mpz_urandomm (bit_size_bound, random_state, bit_size_bound);

  // Generate random number
  mp_bitcnt_t gmp_bit_size_bound = (mp_bitcnt_t) mpz_get_ui(bit_size_bound);
  mpz_urandomb(random_num, random_state, gmp_bit_size_bound);

  // Garbage collection
  mpz_clear(bit_size_bound);
  gmp_randclear(random_state);
}

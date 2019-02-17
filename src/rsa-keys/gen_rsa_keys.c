#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rsa-keys.h"
#include "../io-utils/io-utils.h"
#include "../math-utils/math-utils.h"

struct rsa_keys gen_rsa_keys () {

  struct rsa_keys rsa_keys;

  long int first_prime, second_prime, p, q;

  do {

    first_prime = gen_prime();
    second_prime = gen_prime();

    if (first_prime > second_prime) {
      p = first_prime;
      q = second_prime;
    } else if (first_prime < second_prime) {
      p = second_prime;
      q = first_prime;
    }
  } while (first_prime == second_prime);

  long long int N = ((long long int) p) * ((long long int) q);

  long long int euler_totient = ((long long int) (p - 1)) * ((long long int) (q - 1));
  long long int euler_totient_coeff;

  long long int e, d, gcd;

  int exit_status_code_EEA;

  do {

    do {

      e = (long long int) gen_prime();
    } while (e >= euler_totient);

    exit_status_code_EEA = ext_eucl_alg_lli(euler_totient, e, &gcd, &euler_totient_coeff, &d);
  } while (exit_status_code_EEA != 0 || gcd != 1);

  if (d < 0) {
    d = d + euler_totient;
  }

  rsa_keys.N = N;
  rsa_keys.e = e;
  rsa_keys.d = d;

  return rsa_keys;
}

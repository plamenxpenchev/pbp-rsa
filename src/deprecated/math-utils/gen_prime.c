#include <stdio.h>
#include <stdlib.h>
#include <bsd/stdlib.h>
#include <math.h>
#include "math-utils.h"

#define LONG_LONG_INT_UPPER_BOUND 9223372036854775807

int check_primality (long int num) {

	if (num <= 1) {
		return 1;
	}

	for (long int i = 2; i*i <= num; i++) {
			if (mod_li(num, i) == 0) {
				return 1;
			}
	}

	return 0;
}

void find_prime (long int *prime, long int interval_begin, long int interval_end) {

	*prime = 1;
	for (long int num = interval_begin; num < interval_end; num++) {
		if (check_primality(num) == 0) {
			*prime = num;
			break;
		}
	}
}

long int gen_prime () {

	long double long_long_int_upper_bound = (long double) LONG_LONG_INT_UPPER_BOUND;
	long int rsa_primes_upper_bound = (long int) sqrtl(sqrtl(long_long_int_upper_bound));
	long int pnt_primes_gap = (long int) ceil(log((double) rsa_primes_upper_bound));

	long int random_num;
	long int interval_begin;
	long int interval_end;

	long int prime;
	do {

		do {
			random_num = arc4random();
			random_num = labs(random_num);
		} while (random_num >= rsa_primes_upper_bound);

		interval_begin = random_num - pnt_primes_gap;
		interval_end = random_num;

		find_prime(&prime, interval_begin, interval_end);
	} while (prime == 1);

  return prime;
}

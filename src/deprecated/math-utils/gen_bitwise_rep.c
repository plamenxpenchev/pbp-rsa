#include <stdio.h>
#include <stdlib.h>

int gen_powers_of_two(long long int *powers_of_two, long long int exp_bound) {

  int exp_base_two = 0;
  long long int power_of_two = 1;

  powers_of_two[exp_base_two] = power_of_two;

  while (2 * power_of_two <= exp_bound) {

    power_of_two = 2 * power_of_two;
    exp_base_two++;
    powers_of_two[exp_base_two] = power_of_two;
  }

  return exp_base_two;
}

void gen_exp_bitwise_rep(long long int exponent, int bit_pos, int *bitwise_rep_exp, long long int *powers_of_two) {
  bitwise_rep_exp[bit_pos] = 1;
  long long int exp_diff = exponent - powers_of_two[bit_pos];
  for (bit_pos--; bit_pos >= 0; bit_pos--) {

    if (powers_of_two[bit_pos] <= exp_diff) {

      bitwise_rep_exp[bit_pos] = 1;
      exp_diff = exp_diff - powers_of_two[bit_pos];
    } else {

      bitwise_rep_exp[bit_pos] = 0;
    }
  }
}

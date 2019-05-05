#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "io-utils.h"

// Exit codes:
// 0 - success
// 1 - truncated
// 2 - assignment failure
// 3 - EOF
int read_gmp_z(mpz_t key, FILE *fp)
{
  const int DECIMAL_BASE = 10;

  char *ptr_to_next_char_in_str_after_num_value;

  const int MAX_LENGTH = 2000;
  char num_string[MAX_LENGTH];

  int is_input_truncated = 0;
  int num_string_len = read_line(num_string, &is_input_truncated, MAX_LENGTH, fp);

  // EOF
  if (num_string[0] == '\0') {
    return 3;
  }

  // Truncated
  if (is_input_truncated == 1) {
    return 1;
  }

  int assign_exit_code = mpz_set_str(key, num_string, DECIMAL_BASE);

  // Assignment failure
  if (assign_exit_code == -1) {
    return 2;
  }

  // Success
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "io-utils.h"

// Exit codes:
// 0 - success
// 1 - truncated
// 2 - failure pre-truncation
// 3 - EOF
int read_lli(long long int *long_long_int, FILE *fp){

  int status_code = 0;
  char *ptr_to_next_char_in_str_after_num_value;

  const int MAX_LENGTH = 20;
  char num_string[MAX_LENGTH];

  int is_input_truncated = 0;
  int num_string_len = read_line(num_string, &is_input_truncated, MAX_LENGTH, fp);

  if (num_string[0] == '\0') {
    return 3;
  }

  if (num_string == "0" && num_string_len == 1) {
    *long_long_int = 0;
  } else {
    *long_long_int = strtoll(num_string, &ptr_to_next_char_in_str_after_num_value, 10); // string, ptr to next char in the string after numerical value, base
    if (*long_long_int == 0 || *ptr_to_next_char_in_str_after_num_value) { // exited with 0 (on error) || non-null pointer
      status_code = 2;
    } else if (is_input_truncated == 1) {
      status_code = 1;
    }
  }

  return status_code;
}

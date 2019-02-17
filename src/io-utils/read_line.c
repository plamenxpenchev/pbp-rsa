#include <stdio.h>

int read_line(char string[], int *ptr_is_input_truncated, int truncation_len, FILE *fp) {

  char character;
  int keep_reading = 1;
  int str_len = 0;

  *ptr_is_input_truncated = 0;

  while (keep_reading) {

    if (fp == NULL) {
      character = getchar();
    } else {
      character = fgetc(fp);
    }

    if ((character == '\n') || (character == EOF)) {

      keep_reading = 0;
    } else if (str_len < truncation_len - 1) {

      string[str_len] = character;
      str_len++;
    } else if ((str_len == truncation_len - 1) && (*ptr_is_input_truncated == 0)) {

      *ptr_is_input_truncated = 1;
    }
  }

  string[str_len] = '\0';
  return str_len;
}

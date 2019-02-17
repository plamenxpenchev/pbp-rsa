#include <stdio.h>
#include <stdlib.h>
#include "rsa.h"
#include "./io-utils/io-utils.h"
#include "./rsa-keys/rsa-keys.h"

int get_user_choice() {

  const int MAX_LENGTH = 2;
  char num_string[MAX_LENGTH];

  int is_input_truncated = 0;
  read_line(num_string, &is_input_truncated, MAX_LENGTH, NULL);

  int choice = atoi(num_string);
  int invalid_choice = 1;

  while (invalid_choice) {

    if (is_input_truncated) {
      printf("\nInvalid choice. Enter either 1, 2, or 3:\n");
      read_line(num_string, &is_input_truncated, MAX_LENGTH, NULL);
      choice = atoi(num_string);

      continue;
    }

    switch (choice) {
      case 1:
      case 2:
      case 3:
        invalid_choice = 0;

        break;
      default:
        printf("\nInvalid choice. Enter either 1, 2, or 3:\n");
        read_line(num_string, &is_input_truncated, MAX_LENGTH, NULL);
        choice = atoi(num_string);

        break;
    }
  }

  return choice;
}

int main () {
  printf("\nSelect an action to perform:\n\n");
  printf("1. Generate RSA key pair\n");
  printf("2. Encipher text file\n");
  printf("3. Decipher text file\n");
  printf("\n");

  int user_choice = get_user_choice();
  switch (user_choice) {
    case 1:
      save_rsa_keys();
      printf("Successfully generated RSA keys.\n");
      break;
    case 2:
      rsa_encipher();
      printf("Successfully enciphered the plain text specified.\n");
      break;
    case 3:
      rsa_decipher();
      break;
    default:
      break;
  }

  return 0;
}

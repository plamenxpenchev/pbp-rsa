#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "rsa_menu.h"
#include "rsa.h"
#include "./io-utils/io-utils.h"
#include "./rsa-keys/rsa-keys.h"

int main() {

	while (1) {

		printf("\nSelect an action to perform:\n\n");
		printf("1. Generate RSA key pair\n");
		printf("2. Encipher text file\n");
		printf("3. Decipher text file\n");
		printf("4. Exit\n");
		printf("\n");

		switch (user_choice(4)) {
		case 1:
		{
			mpz_t e;
			mpz_t d;
			mpz_t N;

			mpz_init(e);
			mpz_init(d);
			mpz_init(N);

			// The key size of N
			unsigned long int rsa_key_bit_size;

			printf("\nSelect a key bit size:\n\n");
			printf("1. 1024 (not suggested)\n");
			printf("2. 2048\n");
			printf("3. 4096\n");
			printf("\n");

			switch (user_choice(3)) {
			case 1:
				rsa_key_bit_size = 1024;
				break;
			case 2:
				rsa_key_bit_size = 2048;
				break;
			case 3:
				rsa_key_bit_size = 4096;
				break;
			default:
				break;
			}

			gen_rsa_keys(e, d, N, rsa_key_bit_size);
			save_rsa_keys(e, d, N);

			// Free memory
			mpz_clear(e);
			mpz_clear(d);
			mpz_clear(N);

			printf("Successfully generated RSA keys.\n");
			break;
		}
		case 2:
			rsa_encipher();
			printf("Successfully enciphered the plain text specified.\n");
			break;
		case 3:
			rsa_decipher();
			break;
		case 4:
			printf("Exiting program.\n");
			return 0;
		default:
			break;
		}
	}

	return 0;
}

int user_choice(int choices) {

	const int MAX_LENGTH = 2;
	char num_string[MAX_LENGTH];

	int is_input_truncated = 0;
	read_line(num_string, &is_input_truncated, MAX_LENGTH, NULL);

	int choice = atoi(num_string);
	int invalid_choice = 1;

	while (invalid_choice) {

		if (is_input_truncated) {
			printf("\nInvalid choice. Pick a menu option from 1 to %d:\n", choices);
			read_line(num_string, &is_input_truncated, MAX_LENGTH, NULL);
			choice = atoi(num_string);

			continue;
		}

		if (choice < 1 || choice > choices) {
			printf("\nInvalid choice. Pick a menu option from 1 to %d:\n", choices);
			read_line(num_string, &is_input_truncated, MAX_LENGTH, NULL);
			choice = atoi(num_string);
		} else {
			invalid_choice = 0;
		}
	}

	return choice;
}

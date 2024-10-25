#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "../io-utils/io-utils.h"

void get_rsa_priv_keys(mpz_t d, mpz_t N) {

	FILE* rsa_fp;
	rsa_fp = fopen("exec/keys/rsa", "r");

	if (rsa_fp == NULL) {
		printf("Cannot find your private RSA key. Before you try to decipher any ciphertext directed at you, make sure you have generated a pair of RSA keys, and that the 'rsa' file stays under the 'exec/keys/' directory.\n");
		exit(1);
	}

	read_gmp_z(d, rsa_fp);
	read_gmp_z(N, rsa_fp);

	fclose(rsa_fp);
}

void get_rsa_pub_keys(mpz_t e, mpz_t N) {

	FILE* rsa_pub_fp;
	char foreign_rsa_pub_filename[255];
	printf("Enter the path to the 'rsa.pub' file of the person you wish to send a message to: \n");
	scanf("%s", foreign_rsa_pub_filename);

	rsa_pub_fp = fopen(foreign_rsa_pub_filename, "r");

	while (rsa_pub_fp == NULL) {

		printf("\nFile '%s' was not found. Please try again: \n", foreign_rsa_pub_filename);
		scanf("%s", foreign_rsa_pub_filename);

		rsa_pub_fp = fopen(foreign_rsa_pub_filename, "r");
	}

	read_gmp_z(e, rsa_pub_fp);
	read_gmp_z(N, rsa_pub_fp);

	fclose(rsa_pub_fp);
}

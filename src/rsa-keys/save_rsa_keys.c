#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void save_rsa_keys(mpz_t e, mpz_t d, mpz_t N) {

	FILE* rsa_pub;
	FILE* rsa;

	rsa_pub = fopen("exec/keys/rsa.pub", "w");
	rsa = fopen("exec/keys/rsa", "w");

	char* key;

	const int DECIMAL_BASE = 10;

	key = mpz_get_str(NULL, DECIMAL_BASE, e);
	fprintf(rsa_pub, "%s\n", key);

	key = mpz_get_str(NULL, DECIMAL_BASE, d);
	fprintf(rsa, "%s\n", key);

	key = mpz_get_str(NULL, DECIMAL_BASE, N);
	fprintf(rsa_pub, "%s\n", key);
	fprintf(rsa, "%s\n", key);

	free(key);
	key = NULL;

	fclose(rsa_pub);
	fclose(rsa);
}

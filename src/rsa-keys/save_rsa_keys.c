#include <stdio.h>
#include <stdlib.h>
#include "rsa-keys.h"

void save_rsa_keys() {
  printf("Generating RSA keys...\n");

  struct rsa_keys rsa_keys = gen_rsa_keys();

  FILE *rsa_pub;
  FILE *rsa;

  rsa_pub = fopen("keys/rsa.pub","w");
  rsa = fopen("keys/rsa","w");

  fprintf(rsa_pub, "%lli\n", rsa_keys.e);
  fprintf(rsa_pub, "%lli\n", rsa_keys.N);

  fprintf(rsa, "%lli\n", rsa_keys.d);
  fprintf(rsa, "%lli\n", rsa_keys.N);

  fclose(rsa_pub);
  fclose(rsa);
}

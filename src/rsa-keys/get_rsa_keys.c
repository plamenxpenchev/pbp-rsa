#include <stdio.h>
#include <stdlib.h>
#include "rsa-keys.h"
#include "../io-utils/io-utils.h"

struct rsa_priv_keys get_rsa_priv_keys() {
  FILE *rsa_fp;
  rsa_fp = fopen("keys/rsa","r");

  if (rsa_fp == NULL) {
    printf("Cannot find your private RSA key. Before you try to decipher any ciphertext directed at you, make sure you have generated a pair of RSA keys, and that the 'rsa' file stays under the 'exec/keys/' directory.\n");
    exit (1);
  }

  struct rsa_priv_keys rsa_priv_keys;

  read_lli(&rsa_priv_keys.d, rsa_fp);
  read_lli(&rsa_priv_keys.N, rsa_fp);

  fclose(rsa_fp);

  return rsa_priv_keys;
}

struct rsa_pub_keys get_rsa_pub_keys() {
  FILE *rsa_pub_fp;
  char foreign_rsa_pub_filename[255];
  printf("Enter the path to the 'rsa.pub' file of the person you wish to send a message to: \n");
  scanf("%s", foreign_rsa_pub_filename);

  rsa_pub_fp = fopen(foreign_rsa_pub_filename,"r");

  while (rsa_pub_fp == NULL) {

    printf("\nFile '%s' was not found. Please try again: \n", foreign_rsa_pub_filename);
    scanf("%s", foreign_rsa_pub_filename);

    rsa_pub_fp = fopen(foreign_rsa_pub_filename,"r");
  }

  struct rsa_pub_keys rsa_pub_keys;

  read_lli(&rsa_pub_keys.e, rsa_pub_fp);
  read_lli(&rsa_pub_keys.N, rsa_pub_fp);

  fclose(rsa_pub_fp);

  return rsa_pub_keys;
}

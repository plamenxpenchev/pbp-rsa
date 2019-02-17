#include <stdio.h>
#include <stdlib.h>

FILE * get_file_to_encrypt() {
  FILE *plain_fp;

  char name_pltxt_file[255];
  printf("Enter the path to the file you wish to encrypt: \n");
  scanf("%s", name_pltxt_file);

  plain_fp = fopen(name_pltxt_file,"r");

  while (plain_fp == NULL) {

    printf("\nFile '%s' was not found. Please try again: \n", name_pltxt_file);
    scanf("%s", name_pltxt_file);

    plain_fp = fopen(name_pltxt_file,"r");
  }

  return plain_fp;
}

FILE * get_file_to_decrypt() {
  FILE *cipher_fp;

  char name_cipher_txt_file[255];
  printf("Enter the path to the file you wish to decrypt: \n");
  scanf("%s", name_cipher_txt_file);

  cipher_fp = fopen(name_cipher_txt_file,"r");

  while (cipher_fp == NULL) {

    printf("\nFile '%s' was not found. Please try again: \n", name_cipher_txt_file);
    scanf("%s", name_cipher_txt_file);

    cipher_fp = fopen(name_cipher_txt_file,"r");
  }

  return cipher_fp;
}

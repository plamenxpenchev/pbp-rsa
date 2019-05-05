int read_line(char string[], int *ptr_is_input_truncated, int truncation_len, FILE *fp);
int read_gmp_z(mpz_t key, FILE *fp);
FILE * get_file_to_encrypt();
FILE * get_file_to_decrypt();

void ext_eucl_rec_alg(long long int *i, long long int *r_i_less2, long long int *r_i_less1, long long int *s_i_less2, long long int *s_i_less1, long long int *t_i_less2, long long int *t_i_less1, long long int *r_i, long long int *q_i_less1, long long int *s_i, long long int *t_i);
int verify_gcd_lin_combo(long long int gcd, long long int s_i_less1, long long int r_0, long long int t_i_less1, long long int r_1);
int ext_eucl_alg_lli(long long int r_0, long long int r_1, long long int *gcd, long long int *r_0_param, long long int *r_1_param);
void find_prime (long int *prime, long int interval_begin, long int interval_end);
int check_primality (long int num);
long int gen_prime ();
long int mod_li (long int dividend_long_int, long int divisor_long_int);
long long int mod_lli (long long int dividend_long_long_int, long long int divisor_long_long_int);
int gen_powers_of_two(long long int *powers_of_two, long long int exp_bound);
void gen_exp_bitwise_rep(long long int exponent, int bit_pos, int *bitwise_rep_exp, long long int *powers_of_two);
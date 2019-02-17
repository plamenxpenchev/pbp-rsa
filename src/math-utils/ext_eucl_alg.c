#include <stdio.h>
#include "math-utils.h"

void ext_eucl_rec_alg(long long int *i, long long int *r_i_less2, long long int *r_i_less1, long long int *s_i_less2, long long int *s_i_less1, long long int *t_i_less2, long long int *t_i_less1, long long int *r_i, long long int *q_i_less1, long long int *s_i, long long int *t_i)
{
  *r_i = mod_lli((*r_i_less2), (*r_i_less1));
  *q_i_less1 = ((*r_i_less2)-(*r_i))/(*r_i_less1);

  *s_i = (*s_i_less2)-(*q_i_less1)*(*s_i_less1);
  *t_i = (*t_i_less2)-(*q_i_less1)*(*t_i_less1);

  if (*r_i != 0) { // r_i == 0 => gcd(r_0,r_1) = r_i_less1 = s_i_less1*r_0 + t_i_less1*r_1

    // Prepare the next iteration
    *i = (*i) + 1;

    *r_i_less2 = *r_i_less1;
    *r_i_less1 = *r_i;

    *s_i_less2 = *s_i_less1;
    *s_i_less1 = *s_i;

    *t_i_less2 = *t_i_less1;
    *t_i_less1 = *t_i;

    ext_eucl_rec_alg(i, r_i_less2, r_i_less1, s_i_less2, s_i_less1, t_i_less2, t_i_less1, r_i, q_i_less1, s_i, t_i);
  }
}

int verify_gcd_lin_combo(long long int gcd, long long int s_i_less1, long long int r_0, long long int t_i_less1, long long int r_1)
{
  long long int gcd_lin_combo = s_i_less1*r_0 + t_i_less1*r_1;
  if (gcd == gcd_lin_combo) {
    return 0;
  } else {
    return 1;
  }
}

// gcd (r_0, r_1) = s_i_less1 * r_0 + t_i_less1 * r_1
int ext_eucl_alg_lli(long long int r_0, long long int r_1, long long int *gcd, long long int *r_0_param, long long int *r_1_param)
{
  // Final parameters
  long long int *s_i_less1 = r_0_param;
  long long int *t_i_less1 = r_1_param;

  // Prepare initial state of the recursion
  long long int i = 2;

  long long int r_i_less2 = r_0;
  long long int r_i_less1 = r_1;

  long long int s_i_less2 = 1;
  *s_i_less1 = 0;

  long long int t_i_less2 = 0;
  *t_i_less1 = 1;

  long long int r_i, q_i_less1, s_i, t_i;

  ext_eucl_rec_alg(&i, &r_i_less2, &r_i_less1, &s_i_less2, s_i_less1, &t_i_less2, t_i_less1, &r_i, &q_i_less1, &s_i, &t_i);
  *gcd = r_i_less1;

  int verify_eea_status_code = verify_gcd_lin_combo(*gcd, *s_i_less1, r_0, *t_i_less1, r_1);
  return verify_eea_status_code;
}

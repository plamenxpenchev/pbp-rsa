struct rsa_keys {
   long long int e;
   long long int d;
   long long int N;
};
struct rsa_pub_keys {
   long long int e;
   long long int N;
};
struct rsa_priv_keys {
   long long int d;
   long long int N;
};
struct rsa_keys gen_rsa_keys();
void save_rsa_keys();
struct rsa_priv_keys get_rsa_priv_keys();
struct rsa_pub_keys get_rsa_pub_keys();

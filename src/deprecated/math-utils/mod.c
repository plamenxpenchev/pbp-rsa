#include <stdio.h>
#include <math.h>

long int mod_li(long int dividend_long_int, long int divisor_long_int) {

	long double dividend_long_double = (long double) dividend_long_int;
	long double divisor_long_double = (long double) divisor_long_int;

	return (long int) fmodl(dividend_long_double, divisor_long_double);
}

long long int mod_lli(long long int dividend_long_long_int, long long int divisor_long_long_int) {

	long double dividend_long_double = (long double) dividend_long_long_int;
	long double divisor_long_double = (long double) divisor_long_long_int;

	return (long long int) fmodl(dividend_long_double, divisor_long_double);
}

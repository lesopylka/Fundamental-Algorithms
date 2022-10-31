#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

long double limit(long double lim(int n), double eps);
long double e_lim(int n);
long double pi_lim(int n);
long double ln2_lim(int n);
long double sqrt2_lim(double eps);
long double euler_lim(double eps);

long double _fabs(long double x) {
    return x > 0 ? x : -x;
}

long double limit(long double lim(int n), double eps)
{
	int i = 1 / eps / eps, step = 1 / eps;
	long double res = 0, prev_res = 0;
	eps *= eps;

	while (_fabs(res - prev_res) > eps || prev_res == 0) {
		prev_res = res;
		res = lim(i += step);
	}

	return res;
}

long double sum(long double function(int n), double eps, int start)
{
	long double res = 0, prev_res = 0;
	for (int k = start; (_fabs(res - prev_res) > eps || _fabs(prev_res) < eps || (res - prev_res == 0)); k++) {
		prev_res = res;
		res += function(k);
	}
	return res;
}

long double mult(long double function(int n), double eps, int start)
{
	long double res = 1, prev_res = 0, eps_func = eps / 10;
	for (int k = start; _fabs(prev_res - res) > eps_func || _fabs(prev_res) < eps; k++) {
		prev_res = res;
		res *= function(k);
	}
	return res;
}

long double factorial(int num)
{
	if (num == 0) {
		return 1;
	}
	int res = 1;
	while (num > 0) {
		res *= num;
		num--;
	}
	return res;
}

long double e_lim(int n)
{
	return pow(1 + 1.0 / n, n);
}

long double pi_lim(int n)
{
	int tmp = n;
	long double res = 1;
	while (tmp) {
		res *= 4.0 * tmp * tmp / (2 * tmp) / (2 * tmp - 1);
		tmp--;
	}
	res /= sqrt(n);
	return res *= res;
}

long double ln2_lim(int n)
{
	return n * (pow(2, 1.0 / n) - 1);
}

long double sqrt2_lim(double eps)
{
	int i = 0, j;
	long double res = -0.5, prev_res = 0;
	eps *= eps;

	while (_fabs(res - prev_res) > eps || prev_res == 0) {
		prev_res = res;
		res = res - ((res * res) / 2) + 1;
	}

	return res;
}

long double e_row(int n)
{
	return 1.0 / factorial(n);
}

long double pi_row(int n)
{
	return 4 * pow(-1.0, n - 1) / (2.0 * n - 1);
}

long double ln2_row(int n)
{
	return pow(-1.0, n - 1) / n;
}

long double sqrt2_mult(int k)
{
	return pow(2, pow(2, -k));
}

long double gamma_row(double eps, int start)
{
	long double res = 0, eps_func = 1e-15, prev_res = 0, func_returned = 0;

	for (int k = start; (_fabs(res - prev_res) > eps_func || _fabs(prev_res) < eps || (res - prev_res == 0)); k++) {
		prev_res = res;
		func_returned = 1.0 / pow(floor(sqrt(k)), 2) - 1.0 / k;
		res += func_returned;
	}
	return res;
}

double equation_dichotomy(double equation(double x), double a, double b, double eps)
{
	double funct_result_middle;
	while (_fabs(a - b) > eps) {
		funct_result_middle = equation((a + b) / 2);
		if (equation(a) * funct_result_middle > 0) {
			a = (a + b) / 2;
		}

		if (equation(b) * funct_result_middle > 0) {
			b = (a + b) / 2;
		}
	}
	return (a + b) / 2;
}

double e_equation(double x)
{
	return log(x) - 1;
}

double pi_equation(double x)
{
	return -sin(x);
}

double ln2_equation(double x)
{
	return pow(M_E, x) - 2;
}

double sqrt2_equation(double x)
{
	return x * x - 2;
}

void simple_nums_generate(long** simple_nums, unsigned long long to_generate, unsigned long long* generated)
{
	int count = 0;
	long *tmp = NULL, i, j, * array_sieve = NULL;

	if (!(array_sieve = (long*)calloc((to_generate + 1), sizeof(long)))) {
		return;
	}

	for (int i = 2; i <= to_generate; i++) {
		if (!array_sieve[i]) {
			count++;
			for (int j = i + i; j <= to_generate; j += i) {
				array_sieve[j] = 1;
			}
		}
	}
	
	if ((*simple_nums == NULL || (*generated) == 0)) {
		if (!((*simple_nums) = (long*)calloc(count, sizeof(long)))) {
			return;
		}
	}
	else {
		if (!(tmp = (long*)realloc((*simple_nums), sizeof(long) * (count + (*generated))))) {
			free(*simple_nums);
			return;
		}
		(*simple_nums) = tmp;
	}
	
	i = (!(*generated) ? 2 : (*simple_nums)[(*generated) - 1] + 1);
	for (int i = 0; i <= to_generate; i++) {
		if (!array_sieve[i]) {
			(*simple_nums)[(*generated)++] = i;
		}
	}

	free(array_sieve);

}

double euler_equation(double eps)
{
	double result = 1, prev_result = 0;
	int step = 1. / eps / 100;
	long* simple_nums = NULL;
	unsigned long long t = 1.0 / eps / eps, generated = 0, i;
	eps /= 1000;

	for (int t = 0; _fabs(result - prev_result) > eps; t += step) {
		prev_result = result;
		result = 1;
		simple_nums_generate(&simple_nums, t, &generated);
		for (int i = 0; i < generated; i++) {
			result *= (double)(simple_nums[i] - 1) / simple_nums[i];
		}
		result *= log(t);
		result = -log(result);
	}

	free(simple_nums);
	return result;
}

void pascal_table_generate(unsigned long long*** table, int* generated, int to_generate)
{
	unsigned long long** tmp_table = NULL, * tmp_string = NULL;
	if (!(*generated)) {
		if (!((**table) = (unsigned long long*)malloc(sizeof(unsigned long long)))) {
			return;
		}
		(*table)[0][0] = 1;
		(*generated)++;
	}

	// gen enough strings
	if (!(tmp_table = (unsigned long long**)realloc((*table), sizeof(unsigned long long*) * (to_generate + 1)))) {
		return;
	}
	(*table) = tmp_table;

	int str, col, string_items_count;
	for (str = (*generated); str < to_generate + 1; str++) {
		// gen array (string) with enough memory for items
		string_items_count = str + 1;
		if (!((*table)[str] = (unsigned long long*)malloc(sizeof(unsigned long long) * string_items_count))) {
			return;
		}
		
		for (col = 0; col <= str; col++) {
			if (col == 0 || col == str) {
				(*table)[str][col] = 1;
			}

			else {
				(*table)[str][col] = (*table)[str - 1][col - 1] + (*table)[str - 1][col];
			}
		}
	}
	(*generated) = str;
}

long double euler_lim(double eps)
{
	unsigned long long** pascal_table = NULL;
	if (!(pascal_table = (unsigned long long**)calloc(1, sizeof(long*)))) {
		return NAN;
	}

	int k, m = 32, i = 0, generated_strings = 0;
	long double partial_sum = 1, log_sum = 0, res = 0, prev_res = 0;
	eps /= 100;

	while (_fabs(prev_res - res) > eps || _fabs(prev_res - res) == 0) {
		prev_res = res;
		res = 0;
		log_sum = 0;
		partial_sum = 1;

		pascal_table_generate(&pascal_table, &generated_strings, m);

		for (int k = 1; k <= m; k++) {
			partial_sum *= (long double)pascal_table[m][k] / k;
			partial_sum *= (long double)(k & 1 ? -1 : 1);

			log_sum += log(k);

			res += log_sum * partial_sum;
			partial_sum = 1;
		}
		m++;
	}

	for (int i = 0; i < generated_strings; i++) {
		free(pascal_table[i]);
	}
	free(pascal_table);

	return res;
}



int main(void)
{
	int l;
	printf("Enter precision:\n");
	scanf("%d", &l);
 	double eps = pow(10, -l);
	l++; 
	
	printf("e constant:\n");
	printf("\tas limit value: %.*Lf\n", l, limit(e_lim, eps));
	printf("\tas row sum: %.*Lf\n", l, sum(e_row, eps, 0));
	printf("\tas solution of an equation: %.*lf\n\n", l, equation_dichotomy(e_equation, 2., 3., eps));

	printf("pi constant:\n");
	printf("\tas limit value: %.*Lf\n", l, limit(pi_lim, eps));
	printf("\tas row sum: %.*Lf\n", l, sum(pi_row, eps, 1));
	printf("\tas solution of an equation: %.*lf\n\n", l, equation_dichotomy(pi_equation, 3, 3.5, eps));
	
	printf("ln(2) constant:\n");
	printf("\tas limit value: %.*Lf\n", l, limit(ln2_lim, eps));
	printf("\tas row sum: %.*Lf\n", l, sum(ln2_row, eps, 1));
	printf("\tas solution of an equation: %.*lf\n\n", l, equation_dichotomy(ln2_equation, 0, 1, eps));

	printf("sqrt(2) constant:\n");
	printf("\tas limit value: %.*Lf\n", l, sqrt2_lim(eps));
	printf("\tas row product: %.*Lf\n", l, mult(sqrt2_mult, eps, 2));
	printf("\tas solution of an equation: %.*lf\n\n", l, equation_dichotomy(sqrt2_equation, 1, 2, eps));
	
	printf("Euler's constant:\n");
	printf("\tas limit value: %.*Lf\n", l, euler_lim(eps));
	double constant_pi = M_PI * M_PI / 6;
	printf("\tas row sum: %.*Lf\n", l, gamma_row(eps, 2) - constant_pi);
	printf("\tas solution of an equation: %.*lf\n\n", l, euler_equation(eps));

	return 0;
}

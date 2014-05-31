#include <stdio.h>

extern int read_doubles(FILE *, double *, int);
#define MAX 100

int main() {
	int i, n;

	double a[MAX];

	n = read_doubles(stdin, a, MAX);

	for (i = 0; i < n; i++)
		printf("%3d %g\n", i, a[i]);
	return 0;
}

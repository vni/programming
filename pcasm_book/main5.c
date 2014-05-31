#include <stdio.h>

void calc_sum(int, int *);

int main(void) {
	int n, sum;

	printf("Sum integers up to: ");
	scanf("%d", &n);
	calc_sum(n, &sum);
	printf("Sum is %d\n", sum);
	return 0;
}

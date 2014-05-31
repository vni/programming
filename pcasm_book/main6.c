#include <stdio.h>

int main(void) {
	int n, sum;

	printf("Sum integers up to: ");
	scanf("%d", &n);
	sum = calc_sum(n);
	printf("Sum is %d\n", sum);
	return 0;
}

#include <stdio.h>

int main(int argc, char *argv[]) {
	unsigned guess, factor, limit;

	limit = atoi(argv[1]);

	/*printf("Find primes up to: ");*/
	/*scanf("%u", &limit);*/
	printf("2\n");
	printf("3\n");
	guess = 5;
	while (guess <= limit) {
		factor = 3;
		while ((factor*factor) < guess && (guess%factor) != 0)
			factor += 2;
		if ((guess%factor) != 0)
			printf("%d\n", guess);
		guess += 2;
	}
}

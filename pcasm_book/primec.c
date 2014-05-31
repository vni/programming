int main(void) {
	int printf(const char *fmt, ...);
	int	scanf(const char *fmt, ...);
	unsigned guess;
	unsigned factor;
	unsigned limit;

	printf("Find primes up to: ");
	scanf("%d", &limit);
	printf("2\n");
	printf("3\n");

	guess = 5;
	while (guess < limit) {
		factor = 3;
		while (factor*factor < guess && guess % factor != 0)
			factor += 2;
		if (guess % factor != 0)
			printf("%d\n", guess);
		guess += 2;
	}

	return 0;
}

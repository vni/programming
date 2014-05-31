int printf(const char *fmt, ...);
int atoi(const char *);
double atof(const char *);

double fscale(double, int);

int main(int argc, char *argv[]) {
	if (argc != 3)
		return 1;
	double d1 = atof(argv[1]);
	int pow = atoi(argv[2]);

	printf("fscale(%f, %d) = %f\n", d1, pow, fscale(d1, pow));
	return 0;
}

int printf(const char *fmt, ...);
double atof(const char *);

double dmax(double d1, double d2);

int main(int argc, char *argv[]) {
	if (argc != 3)
		return 1;
	double d1 = atof(argv[1]);
	double d2 = atof(argv[2]);
	printf("dmax(%g, %g) = %g\n", d1, d2, dmax(d1, d2));
	return 0;
}

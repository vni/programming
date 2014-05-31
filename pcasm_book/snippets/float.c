#include <stdio.h>

void float_binary_print(unsigned int x) {
	unsigned int mask = 0x80000000;
	int i;

	printf("\033[33;1m%c\033[0m", (x & mask) ? '1' : '0');
	mask >>= 1;
	printf(" ");
	for (i = 0; i < 8; i++) {
		printf("\033[36;1m%c\033[0m", (x & mask) ? '1' : '0');
		mask >>= 1;
	}
	printf(" ");
	for (i = 0; i < 23; i++) {
		printf("\033[32;1m%c\033[0m", (x & mask) ? '1' : '0');
		mask >>= 1;
	}
}

void double_binary_print(unsigned int x, unsigned int y) {
	unsigned int mask = 0x80000000;
	int i;

	printf("\033[33;1m%c\033[0m", (x & mask) ? '1' : '0');
	mask >>= 1;
	printf(" ");
	for (i = 0; i < 11; i++) {
		printf("\033[36;1m%c\033[0m", (x & mask) ? '1' : '0');
		mask >>= 1;
	}
	printf(" ");
	for (i = 0; i < 20; i++) {
		printf("\033[32;1m%c\033[0m", (x & mask) ? '1' : '0');
		mask >>= 1;
	}
	mask = 0x80000000;
	for (i = 0; i < 32; i++) {
		printf("\033[32;1m%c\033[0m", (y & mask) ? '1' : '0');
		mask >>= 1;
	}
}

int main(void) {
	/* const char f1[] = { 0xCC, 0xCC, 0xBE, 0x41 }; */ /* 0x41BECCCC Beware! Little Endian */
	/* const char f2[] = { 0xCD, 0xCC, 0xBE, 0x41 }; */ /* 0x41BECCCD Beware! Little Endian */
	unsigned int f1 = 0x41BECCCC;
	unsigned int f2 = 0x41BECCCD;
	float f3 = 23.85;

	unsigned int plus_zero = 0x00000000;
	unsigned int minus_zero = 0x80000000;
	unsigned int plus_inf = 0x7F800000;
	unsigned int minus_inf = 0xFF800000;
	unsigned int plus_nan = 0x7F855555;
	unsigned int minus_nan = 0xFF882312;
	unsigned int plus_denorm = 0x00120000;
	unsigned int minus_denorm = 0x80120000;
	float denorm = 1.6530e-39;

	/* char double_precision[] = { 0x40, 0x37, 0xD9, 0x99, 0x99, 0x99, 0x99, 0x9A }; */ /* BIG ENDIAN */
	char double_precision[] = { 0x9A, 0x99, 0x99, 0x99, 0x99, 0xD9, 0x37, 0x40 }; /* LITTLE ENDIAN */
	double d1 = 23.85;

	float_binary_print(f1);
	printf("\nf1: %.12f, 0x%08X\n\n", *(float*)&f1, *(unsigned int *)&f1);
	float_binary_print(f2);
	printf("\nf2: %.12f, 0x%08X\n\n", *(float*)&f2, *(unsigned int *)&f2);
	float_binary_print(*(unsigned int *)&f3);
	printf("\nf3: %.12f, 0x%08X\n\n", f3, *(unsigned int *)&f3);

	printf("PLUS and MINUS ZEROES:\n");
	float_binary_print(plus_zero);
	printf("\nplus_zero: %.12f, 0x%08X\n\n", *(float*)&plus_zero, plus_zero);
	float_binary_print(minus_zero);
	printf("\nminus_zero: %.12f, 0x%08X\n\n", *(float*)&minus_zero, minus_zero);

	printf("PLUS and MINUS INFINITY:\n");
	float_binary_print(plus_inf);
	printf("\nplus_inf: %.12f, 0x%08X\n\n", *(float*)&plus_inf, plus_inf);
	float_binary_print(minus_inf);
	printf("\nminus_inf: %.12f, 0x%08X\n\n", *(float*)&minus_inf, minus_inf);

	printf("PLUS and MINUS Not-a-Number:\n");
	float_binary_print(plus_nan);
	printf("\nplus_nan: %.12f, 0x%08X\n\n", *(float*)&plus_nan, plus_nan);
	float_binary_print(minus_nan);
	printf("\nminus_nan: %.12f, 0x%08X\n\n", *(float*)&minus_nan, minus_nan);

	printf("PLUS and MINUS Denormalized number:\n");
	float_binary_print(plus_denorm);
	printf("\nplus_denorm: %.12f, 0x%08X\n\n", *(float*)&plus_denorm, plus_denorm);
	float_binary_print(minus_denorm);
	printf("\nminus_denorm: %.12f, 0x%08X\n\n", *(float*)&minus_denorm, minus_denorm);
	float_binary_print(*(unsigned int *)&denorm);
	printf("\ndenorm: %.12f, 0x%08X\n\n", denorm, *(unsigned int *)&denorm);

	printf("DOUBLE PRECISION FLOATING POINT NUMBER:\n");
	double_binary_print(*(unsigned int*)(double_precision+4), *((unsigned int *)double_precision));
	printf("\ndouble_precision: %.20f\n\n", *(double*)double_precision);
	double_binary_print(*(((unsigned int*)&d1)+1), *(unsigned int*)&d1);
	printf("\nd1: %.20f\n\n", d1);
	return 0;
}

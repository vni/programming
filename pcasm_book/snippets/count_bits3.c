#include <stdio.h>

int count_bits3(unsigned int x) {
	static unsigned int mask[] = {
		0x55555555,
		0x33333333,
		0x0F0F0F0F,
		0x00FF00FF,
		0x0000FFFF
	};
	int i;
	int shift;
	for (i = 0, shift = 1; i < 5; i++, shift *= 2)
		x = (x & mask[i]) + ((x >> shift) & mask[i]);
	return x;
}

int main(int argc, char *argv[]) {
	if (argv[1]) {
		int cnt = count_bits3(strtol(argv[1], NULL, 0));
		printf("count_bits3(%s) = %d\n", argv[1], cnt);
	}
	return 0;
}

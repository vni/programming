#include <stdio.h>

int bit_counter(int);

int main(void) {
	printf("main() called\n");
	printf("add_2(5): %d\n", add_2(5));
	printf("bit_counter(0x01): %d\n", bit_counter(0x01));
	printf("bit_counter(0x05): %d\n", bit_counter(0x05));
	printf("bit_counter(0x55): %d\n", bit_counter(0x55));
	printf("bit_counter(0x55): %d\n", bit_counter(0x55));
	printf("bit_counter(0x55): %d\n", bit_counter(0x55));
	return 55;
}

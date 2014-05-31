#include <stdio.h>

static unsigned char byte_bit_count[256];

void initialize_count_bits() {
	int cnt, i, data;

	for (i = 0; i < 256; i++) {
		cnt = 0;
		data = i;
		while (data) {
			data = data & (data - 1);
			cnt++;
		}
		byte_bit_count[i] = cnt;
	}
}

int count_bits2(unsigned int data) {
	const unsigned char *byte = (unsigned char *)&data;

	return byte_bit_count[byte[0]] + byte_bit_count[byte[1]] +
		byte_bit_count[byte[2]] + byte_bit_count[byte[3]];
}

int main(int argc, char *argv[]) {
	if (argv[1]) {
		initialize_count_bits();
		int cnt = count_bits2(strtol(argv[1], NULL, 0));
		printf("count_bits2(%s) = %d\n", argv[1], cnt);
	}
	return 0;
}

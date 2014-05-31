#include <stdio.h>

int count_bits1(unsigned int data) {
	int cnt = 0;
	while (data) {
		data = data & (data - 1);
		cnt++;
	}
	return cnt;
}

int main(int argc, char *argv[]) {
	if (argv[1]) {
		int cnt = count_bits1(strtol(argv[1], NULL, 0));
		printf("count_bits1(%s) = %d\n", argv[1], cnt);
	}
	return 0;
}

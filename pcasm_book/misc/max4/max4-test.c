#include <stdio.h>

int max4(int, int, int, int);

int main(void) {
	printf("max(5, 10, 15, 2) = %d\n", max4(5, 10, 15, 2));
	printf("max(5, 20, 15, 2) = %d\n", max4(5, 20, 15, 2));
	printf("max(5, 5, 1, 2) = %d\n", max4(5, 5, 1, 2));
	printf("max(-500, -105, 1, -1000) = %d\n", max4(-500, -105, 1, -1000));
	return 0;
}

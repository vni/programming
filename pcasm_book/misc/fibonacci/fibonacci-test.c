#include <stdio.h>
#include <stdlib.h>

int fibonacci(int);

int main(int argc, char *argv[]) {
	int arg;
	if (argc != 2) {
		printf("Argument expected.\n");
		return 1;
	}
	arg = atoi(argv[1]);
	printf("fibonacci(%d) = %d\n", arg, fibonacci(arg));
	return 0;
}

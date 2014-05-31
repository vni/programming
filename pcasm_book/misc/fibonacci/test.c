#include <stdio.h>

int fibonacci(int arg)
{
	if (arg == 0)
		return 0;
	if (arg == 1)
		return 1;
	return fibonacci(arg-1) + fibonacci(arg-2);
}

int main(int argc, char *argv[])
{
	int i;
	for (i = 0; i < 20; i++)
		printf("   %d", fibonacci(i));
	printf("\n");
	return 0;
}

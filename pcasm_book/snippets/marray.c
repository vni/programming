#include <stdio.h>

void f(int a[][2]) {
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 2; j++)
			printf("a[%d][%d] = %d\n", i, j, a[i][j]);
}

void g(int aaa[][3][2]) {
	int i, j, k;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 2; k++)
				printf("aaa[%d][%d][%d] = %d\n", i, j, k, aaa[i][j][k]);
}

int main(void) {
	int array[3][2] = { { 10, 11 }, { 20, 22 }, { 30, 33 } };
	int aaarray[4][3][2] = {
		{ { 110, 111 }, { 120, 122 }, { 130, 133 } },
		{ { 210, 211 }, { 220, 222 }, { 230, 233 } },
		{ { 310, 311 }, { 320, 322 }, { 330, 333 } },
		{ { 410, 411 }, { 420, 422 }, { 430, 433 } },
	};
	f(array);
	g(aaarray);
	return 0;
}

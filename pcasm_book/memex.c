#include <stdio.h>

#define STR_SIZE 30

void asm_copy(void *, const void *, unsigned);
void *asm_find(const void *, char target, unsigned);
unsigned asm_strlen(const char *);
void asm_strcpy(char *, const char *);

int main() {
	char st1[STR_SIZE] = "test string";
	char st2[STR_SIZE];
	char *st;
	char ch;

	asm_copy(st2, st1, STR_SIZE);
	printf("%s\n", st2);

	printf("Enter a char: ");
	scanf("%c%*[^\n]", &ch);
	st = asm_find(st2, ch, STR_SIZE);
	if (st)
		printf("Found it: %s\n", st);
	else
		printf("Not found\n");

	st1[0] = 0;
	printf("Enter string: ");
	scanf("%s", st1);
	printf("len = %u\n", asm_strlen(st1));

	asm_strcpy(st2, st1);
	printf("%s\n", st2);

	return 0;
}

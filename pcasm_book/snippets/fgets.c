/*
 * if char is unsigned - we will never reach EOF.
 * EOF in the input will be transformed into 0x000000FF in comparison with EOF.
 *
 * if char is signed - we can read 0xff from the input, 0xff as char will
 * be converted into 0xffffffff as int and we will match EOF (-1 = 0xffffffff).
 * So, the cycle will be terminated before EOF
 */

#include <stdio.h>

int main(void) {
	/*char ch; [> signed char - will terminate on 0xFF in input <]*/
	/*unsigned char ch; [> EOF will be never reached <]*/
	int ch; /* YES! This is a proper way!! */

	while ((ch = fgetc(stdin)) != EOF)
		printf("%c %02hhX\n", ch, ch);
}

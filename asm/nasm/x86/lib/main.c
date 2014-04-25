#include <stdio.h>

#define CARRY_FLAG 0x01
#define PARITY_FLAG 0x04
#define AUX_FLAG	0x10
#define ZERO_FLAG	0x40
#define SIGN_FLAG	0x80

#define OVERFLOW_FLAG 0x0800

int get_eax(void);
int get_ebx(void);
int get_ecx(void);
int get_edx(void);
void dump_regs(void);
void dump_flags(void);

void print_binary(unsigned int dword) {
	unsigned int mask = 0x80000000;
	while (mask) {
		printf("%c", (dword & mask) ? '1' : '0');
		mask >>= 1;
	}
}

void dflags(unsigned int flags) {
	printf("FLAGS _______%c_%c_%c_%c_%c\n",
			flags & SIGN_FLAG ? 'S' : '_',
			flags & ZERO_FLAG ? 'Z' : '_',
			flags & AUX_FLAG ? 'A' : '_',
			flags & PARITY_FLAG ? 'P' : '_',
			flags & CARRY_FLAG ? 'C' : '_');
}

int main(void) {
	int ret = 0;
	unsigned int flags = 0;
	ret = printf("Hello, World!\n"); /* eax contains 14 */
	printf("main. dump_regs:\n");
	dump_regs();
	printf("Now, get functions:\n\n");
	printf("get_eax: %08X\n", get_eax());
	printf("get_ebx: %08X\n", get_ebx());
	printf("get_ecx: %08X\n", get_ecx());
	printf("get_edx: %08X\n", get_edx());
	printf("\n\ndump_flags:\n");
	dump_flags();

	flags = get_flags();
	printf("get_flags: ");
	print_binary(flags);
	printf("\n");

	set_carry();
	flags = get_flags();
	printf("STC flags: ");
	print_binary(flags);
	printf("\n");
	dflags(flags);

	clear_carry();
	flags = get_flags();
	printf("CLC flags: ");
	print_binary(flags);
	printf("\n");
	dflags(flags);

	return 0;
}

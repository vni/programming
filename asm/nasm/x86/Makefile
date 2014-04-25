ALL=first hello use-printf dump-regs

all: $(ALL)

first: first.asm
	nasm -f elf $< -l $@.listing
	ld -melf_i386 $@.o -o $@

hello: hello.asm
	nasm -f elf $< -l $@.listing
	ld -melf_i386 $@.o -o $@

use-printf: use-printf.asm
	nasm -f elf $< -l $@.listing
	gcc -o $@ -m32 $@.o

dump-regs: dump-regs.asm
	nasm -f elf $< -l $@.listing
	gcc -o $@ -m32 $@.o

clean:
	rm *.o *.listing $(ALL)

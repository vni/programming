ALL = carry-flag max

all: $(ALL)

carry-flag: carry-flag.asm
	nasm -f elf carry-flag.asm
	ld -o $@ carry-flag.o -m elf_i386

max: max.o asm_io.o
	gcc -o $@ max.o asm_io.o -m32

max.o: max.asm asm_io.inc
	nasm -f elf max.asm

asm_io.o: asm_io.asm asm_io.inc
	nasm -f elf -d ELF_TYPE $<

clean:
	rm -rf *.o $(ALL)

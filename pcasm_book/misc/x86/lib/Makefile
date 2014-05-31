ALL=dump-regs main

all: $(ALL)

lib.o: lib.asm
	nasm -f elf $< -l $@.listing

main.o: main.c
	gcc -m32 -c $<

main: main.o lib.o
	gcc -m32 $^ -o $@

dump-regs: dump-regs.asm
	nasm -f elf $< -l $@.listing
	gcc -o $@ -m32 $@.o

clean:
	rm -f core.* *.o *.listing $(ALL)

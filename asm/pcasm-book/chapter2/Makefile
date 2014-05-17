CFLAGS=-m32 -g
ALL = movzx movsx cbw fgets cmp cmp-carry adc add

all: $(ALL)

movzx: movzx.asm
	nasm -f elf $< -l $@.listing
	gcc $(CFLAGS) -o $@ $@.o

movsx: movsx.asm
	nasm -f elf $< -l $@.listing
	gcc $(CFLAGS) -o $@ $@.o

cbw: cbw.asm
	nasm -f elf $< -l $@.listing
	gcc $(CFLAGS) -o $@ $@.o

fgets: fgets.c
	gcc $(CFLAGS) -o $@ $<

cmp: cmp.asm
	nasm -f elf $< -l $@.listing
	gcc $(CFLAGS) -o $@ $@.o

cmp-carry: cmp-carry.asm
	nasm -f elf $< -l $@.listing
	gcc $(CFLAGS) -o $@ $@.o

adc: adc.asm
	nasm -f elf $< -l $@.listing
	gcc $(CFLAGS) -o $@ $@.o

add: add.asm
	nasm -f elf $< -l $@.listing
	gcc $(CFLAGS) -o $@ $@.o

clean:
	rm -f core* *.o *.listing $(ALL)

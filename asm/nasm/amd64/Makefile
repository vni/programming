ALL=hello64 use-puts

all: $(ALL)

hello64: hello64.asm
	nasm -f elf64 $< -l $@.listing
	ld $@.o -o $@

use-puts: use-puts.asm
	nasm -f elf64 $< -l $@.listing
	gcc $@.o -o $@

clean:
	rm *.o *.listing $(ALL)

max4: max4.asm max4-test.c
	nasm -f elf $<
	gcc -o $@ max4.o max4-test.c

clean:
	rm *.o max4

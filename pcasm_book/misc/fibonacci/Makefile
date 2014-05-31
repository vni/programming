fibonacci: fibonacci.o fibonacci-test.o
	gcc -o $@ $^

fibonacci.o: fibonacci.asm
	nasm -f elf $<

fibonacci-test.o: fibonacci-test.c
	gcc -c $<

clean:
	rm *.o fibonacci

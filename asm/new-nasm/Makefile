main: main.o lib.o
	gcc -o $@ $^ -m32

main.o: main.c
	gcc -c main.c -m32

lib.o: lib.asm
	nasm -f elf lib.asm

clean:
	rm -rf *.o main

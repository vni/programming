ALL = first math prime primec max sub1 sub2 sub3 sub4 sub5 sub6 array1 memex float-array-sum fcomp quad read fprime

all: $(ALL)

first: first.o driver.o asm_io.o
	gcc -o $@ $^

first.o: first.asm asm_io.inc
	nasm -f elf $<

math: math.o driver.o asm_io.o
	gcc -o $@ $^

math.o: math.asm asm_io.inc
	nasm -f elf $<

prime: prime.o driver.o asm_io.o
	gcc -o $@ $^

prime.o: prime.asm asm_io.inc
	nasm -f elf $<

primec: primec.o
	gcc -o $@ $<

primec.o: primec.c
	gcc -c $<

max: max.o driver.o asm_io.o
	gcc -o $@ $^

max.o: max.asm asm_io.inc
	nasm -f elf $<

sub1: sub1.o driver.o asm_io.o
	gcc -o $@ $^

sub1.o: sub1.asm asm_io.asm
	nasm -f elf $<

sub2: sub2.o driver.o asm_io.o
	gcc -o $@ $^

sub2.o: sub2.asm asm_io.asm
	nasm -f elf $<

sub3: sub3.o driver.o asm_io.o
	gcc -o $@ $^

sub3.o: sub3.asm asm_io.asm
	nasm -f elf $<

sub4: sub4.o main4.o driver.o asm_io.o
	gcc -o $@ $^

sub4.o: sub4.asm asm_io.asm
	nasm -f elf $<

main4.o: main4.asm asm_io.asm
	nasm -f elf $<

sub5: sub5.o main5.o asm_io.o
	gcc -o $@ $^

sub5.o: sub5.asm asm_io.asm
	nasm -f elf $<

main5.o: main5.c
	gcc -c $<

sub6: sub6.o main6.o asm_io.o
	gcc -o $@ $^

sub6.o: sub6.asm asm_io.asm
	nasm -f elf $<

main6.o: main6.c
	gcc -c $<

array1: array1.o array1c.o asm_io.o
	gcc -o $@ $^

array1.o: array1.asm asm_io.asm
	nasm -f elf $<

array1c.o: array1c.c
	gcc -c $<

driver.o: driver.c
	gcc -c $<

asm_io.o: asm_io.asm asm_io.inc
	nasm -f elf -d ELF_TYPE $<

memex:	memory.o memex.o
	gcc -o $@ $^

memory.o: memory.asm
	nasm -f elf $<

memex.o: memex.c
	gcc -c $<

float-array-sum: float-array-sum.asm
	nasm -f elf $< 
	gcc -o $@ float-array-sum.o

fcomp: fcomp.asm
	nasm -f elf $<
	ld -o $@ fcomp.o

dmax: dmax.o dmax-driver.o
	gcc -o $@ $^

dmax.o: dmax.asm
	nasm -f elf $<

dmax-driver.o: dmax-driver.c
	gcc -c $<

fscale: fscale.o fscale-driver.o
	gcc -o $@ $^

fscale.o: fscale.asm
	nasm -f elf $<

fscale-driver.o: fscale-driver.c
	gcc -c $<

quad: quad.o quadt.o
	gcc -o $@ $^

quad.o: quad.asm
	nasm -f elf $<

quadt.o: quadt.c
	gcc -c $<

read: read.o readt.o
	gcc -o $@ $^

read.o: read.asm
	nasm -f elf $<

readt.o: readt.c
	gcc -c $<

fprime: prime2.o fprime.o
	gcc -o $@ $^

prime2.o: prime2.asm
	nasm -f elf prime2.asm

fprime.o: fprime.c
	gcc -c $<

clean:
	rm -rf $(ALL) *.o *.lst

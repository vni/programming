Big_int: Big_int.o big_math.o driver.o
	g++ -o $@ $^

Big_int.o: Big_int.cpp Big_int.h
	g++ -c $<

big_math.o: big_math.asm
	nasm -f elf $<

driver.o: driver.cpp Big_int.h
	g++ -c $<

clean:
	rm -rf Big_int *.o

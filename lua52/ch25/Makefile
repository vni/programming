INCLUDES=$(HOME)/local/include
LIBPATH=$(HOME)/local/lib
LDFLAGS=-lm -ldl

all: 1 3 ex3

1: 1.c
	gcc -I $(INCLUDES) -L $(LIBPATH) -o $@ $< -llua $(LDFLAGS)
3: 3.c
	gcc -I $(INCLUDES) -L $(LIBPATH) -o $@ $< -llua $(LDFLAGS)

ex3: ex3.c
	gcc -I $(INCLUDES) -L $(LIBPATH) -o $@ $< -llua $(LDFLAGS)

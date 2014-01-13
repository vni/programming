INCLUDES=$(HOME)/local/include
LIBPATH=$(HOME)/local/lib
LDFLAGS=-lm -ldl

ALL = sin dir summation mylib.so

all: $(ALL)

sin: sin.c
	gcc -I $(INCLUDES) -L $(LIBPATH) -o $@ $< -llua $(LDFLAGS)

dir: dir.c
	gcc -I $(INCLUDES) -L $(LIBPATH) -o $@ $< -llua $(LDFLAGS)

summation: summation.c
	gcc -I $(INCLUDES) -L $(LIBPATH) -o $@ $< -llua $(LDFLAGS)

mylib.so: mylib.c
	gcc -I $(INCLUDES) -L $(LIBPATH) -o $@ $< -shared -fPIC -Wl,-soname,$@

clean:
	rm -f $(ALL)

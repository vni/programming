INCLUDES=$(HOME)/local/include
LIBPATH=$(HOME)/local/lib
LDFLAGS=-lm -ldl

ALL = sin dir summation table.pack reverse mylib.so

all: $(ALL)

sin: sin.c
	gcc -I $(INCLUDES) -L $(LIBPATH) -o $@ $< -llua $(LDFLAGS)

dir: dir.c
	gcc -I $(INCLUDES) -L $(LIBPATH) -o $@ $< -llua $(LDFLAGS)

summation: summation.c
	gcc -I $(INCLUDES) -L $(LIBPATH) -o $@ $< -llua $(LDFLAGS)

table.pack: table.pack.c
	gcc -I $(INCLUDES) -L $(LIBPATH) -o $@ $< -llua $(LDFLAGS)

reverse: reverse.c
	gcc -I $(INCLUDES) -L $(LIBPATH) -o $@ $< -llua $(LDFLAGS)

mylib.so: mylib.c
	gcc -I $(INCLUDES) -L $(LIBPATH) -o $@ $< -shared -fPIC -Wl,-soname,$@

clean:
	rm -f $(ALL)

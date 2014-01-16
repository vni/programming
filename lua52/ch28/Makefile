INCPATH = $(HOME)/local/include
ALL = ch28.so tuple.so

all: $(ALL)

ch28.so: ch28.c
	gcc -shared -fPIC -Wl,-soname,$@ -I$(INCPATH) -o $@ $<

tuple.so: tuple.c
	gcc -shared -fPIC -Wl,-soname,$@ -I$(INCPATH) -o $@ $<

clean:
	rm -f $(ALL)

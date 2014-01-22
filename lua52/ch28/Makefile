INCPATH = $(HOME)/local/include
ALL = ch28.so tuple.so shared_upvalues.so single_shared_upvalue.so exercies.so registry_transliterate.so

all: $(ALL)

ch28.so: ch28.c
	gcc -shared -fPIC -Wl,-soname,$@ -I$(INCPATH) -o $@ $<

tuple.so: tuple.c
	gcc -shared -fPIC -Wl,-soname,$@ -I$(INCPATH) -o $@ $<

shared_upvalues.so: shared_upvalues.c
	gcc -shared -fPIC -Wl,-soname,$@ -I$(INCPATH) -o $@ $<

single_shared_upvalue.so: single_shared_upvalue.c
	gcc -shared -fPIC -Wl,-soname,$@ -I$(INCPATH) -o $@ $<

exercies.so: exercies.c
	gcc -shared -fPIC -Wl,-soname,$@ -I$(INCPATH) -o $@ $<

registry_transliterate.so: registry_transliterate.c
	gcc -shared -fPIC -Wl,-soname,$@ -I$(INCPATH) -o $@ $<

clean:
	rm -f $(ALL)

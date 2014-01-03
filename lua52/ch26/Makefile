CC=gcc
INCLUDES=-I$(HOME)/local/include
LIB_PATH=-L$(HOME)/local/lib
LIBS=-llua -ldl -lm

ALL = load

all: $(ALL)

load: load.c
	$(CC) -o $@ $< $(INCLUDES) $(LIB_PATH) $(LIBS)

clean:
	rm $(ALL)

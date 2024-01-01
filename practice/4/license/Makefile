CC=gcc
CFLAGS=-o

license: license.c
	$(CC) $(CFLAGS) license license.c $(LDLIBS)

.PHONY: clean

clean:
	rm -f *.o $(objects) license
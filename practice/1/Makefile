cc=gcc
LDLIBS=-lcs50
CFLAGS=-o

debug: debug.c
	$(CC) $(CFLAGS) debug debug.c $(LDLIBS)

half: half.c
	$(CC) $(CFLAGS) half half.c $(LDLIBS)

prime: prime.c
	$(CC) $(CFLAGS) prime prime.c $(LDLIBS)

.PHONY: clean

clean:
	rm -f *.o $(objects) debug half prime
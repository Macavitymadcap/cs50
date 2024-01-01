cc=gcc
LDLIBS=-lcs50
CFLAGS=-o

population: population.c
	$(CC) $(CFLAGS) population population.c $(LDLIBS)

scrabble: scrabble.c
	$(CC) $(CFLAGS) scrabble scrabble.c $(LDLIBS)

.PHONY: clean

clean:
	rm -f *.o $(objects) population scrabble
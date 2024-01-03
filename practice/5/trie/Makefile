CC=gcc
LDLIBS=-lcs50
CFLAGS=-o

trie: trie.c
	$(CC) $(CFLAGS) trie trie.c $(LDLIBS)

.PHONY: clean

clean:
	rm -f *.o $(objects) trie
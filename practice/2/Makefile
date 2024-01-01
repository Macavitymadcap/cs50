cc=gcc
LDLIBS=-lcs50
CFLAGS=-o

atoi: hours.c
	$(CC) $(CFLAGS) hours hours.c $(LDLIBS)

no-vowels: no-vowels.c
	$(CC) $(CFLAGS) no-vowels no-vowels.c $(LDLIBS)

password: password.c
	$(CC) $(CFLAGS) password password.c $(LDLIBS)

.PHONY: clean

clean:
	rm -f *.o $(objects) hours no-vowels password
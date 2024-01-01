cc=gcc
LDLIBS=-lcs50
CFLAGS=-o

atoi: atoi.c
	$(CC) $(CFLAGS) atoi atoi.c $(LDLIBS)

temps: temps.c
	$(CC) $(CFLAGS) temps temps.c $(LDLIBS)

max: max.c
	$(CC) $(CFLAGS) max max.c $(LDLIBS)

snackbar: snackbar.c
	$(CC) $(CFLAGS) snackbar snackbar.c $(LDLIBS)

.PHONY: clean

clean:
	rm -f *.o $(objects) qtoi temps mac snackbar
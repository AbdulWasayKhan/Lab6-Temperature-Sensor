CC=gcc
CFLAGS=-lWarn -pedantic

Temperature:	Temperature.o libmyifttt.a
	$(CC) Temperature.o -L. -LwiringPi -lmyifttt -lcurl -o Temperature

libmyifttt.a:	ifttt.o
	ar -rcs libmyifttt.a ifttt.o

ifttt.o:	ifttt.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

Temperature.o:	Temperature.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

all:	Temperature

clean:
	rm Temperature *.o

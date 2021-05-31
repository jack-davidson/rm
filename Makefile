.POSIX:

PREFIX = ~/.local/

all: clean rr

rr: rr.o
	${CC} -o rr rr.o

rr.o:
	${CC} -c rr.c

install:
	cp -f rr ${PREFIX}/bin/rr

clean:
	rm -f *.o rr

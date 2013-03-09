include ../config.mk

wcat: obj
	$(CC) wcat.o -o wcat

obj: wcat.c
	$(CC) -c wcat.c

install:
	install -m 755 wcat $(PREFIX)/bin

uninstall:
	rm -f $(PREFIX)/bin/wcat

clean:
	rm -f wcat *.o

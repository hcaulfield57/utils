include ../config.mk

all: jdate.c
	@echo "CC jdate.c"
	@${CC} ${CFLAGS} jdate.c -o jdate

install:
	install -m 755 jdate ${PREFIX}/bin	

uninstall:
	rm -f ${PREFIX}/bin/jdate

clean:
	rm -f jdate

include ../config.mk

all: newmail.c
	@echo "CC newmail.c"
	@${CC} ${CFLAGS} newmail.c -o newmail

install:
	install -m 755 newmail ${PREFIX}/bin	

uninstall:
	rm -f ${PREFIX}/bin/newmail

clean:
	rm -f newmail

SUBDIRS = jdate newmail

all:
	@for i in ${SUBDIRS}; do cd $$i; ${MAKE} || exit; cd ..; done

install:
	@for i in ${SUBDIRS}; do cd $$i; ${MAKE} install || exit; cd ..; done

uninstall:
	@for i in ${SUBDIRS}; do cd $$i; ${MAKE} uninstall || exit; cd ..; done

clean:
	@for i in ${SUBDIRS}; do cd $$i; ${MAKE} clean || exit; cd ..; done

.PHONY: all install uninstall clean

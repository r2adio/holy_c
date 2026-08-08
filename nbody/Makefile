# nbody - n-body simulation

include config.mk

SRC = nbody.c
OBJ = $(SRC:.c=.o)

all: nbody

.c.o:
	$(CC) -c $(CFLAGS) $<

$(OBJ): config.mk

nbody: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

run: nbody
	./nbody

clean:
	rm -f nbody $(OBJ) nbody-$(VERSION).tar.gz

dist: clean
	mkdir -p nbody-$(VERSION)
	cp Makefile readme config.mk $(SRC) nbody-$(VERSION)
	tar -cf nbody-$(VERSION).tar nbody-$(VERSION)
	gzip nbody-$(VERSION).tar
	rm -rf nbody-$(VERSION)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f nbody $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/nbody

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/nbody

.PHONY: all run clean dist install uninstall

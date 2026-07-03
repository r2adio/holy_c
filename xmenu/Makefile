CC = /Library/Developer/CommandLineTools/usr/bin/clang
SYSROOT = /Library/Developer/CommandLineTools/SDKs/MacOSX26.5.sdk
CFLAGS = -Wall -Wextra -isysroot $(SYSROOT)
LDFLAGS = -lcurses

xmenu: main.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

run: xmenu
	./xmenu

clean:
	rm -f xmenu

.PHONY: clean xmenu

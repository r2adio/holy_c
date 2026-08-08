# nbody version
VERSION = 0.1

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

# raylib
RAYLIBINC = $(shell pkg-config --cflags raylib)
RAYLIBLIB = $(shell pkg-config --libs raylib)

# macOS, uncomment
#MANPREFIX = $(PREFIX)/share/man
MACOSLIBS = -framework Cocoa -framework IOKit -framework CoreVideo

# includes and libs
INCS = $(RAYLIBINC)
LIBS = $(RAYLIBLIB) $(MACOSLIBS)

# flags
CPPFLAGS = -DVERSION=\"$(VERSION)\"
CFLAGS   = -std=c23 -pedantic -Wall -Os $(INCS) $(CPPFLAGS)
LDFLAGS  = $(LIBS)

# compiler and linker
CC = gcc

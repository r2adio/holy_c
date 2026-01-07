CC=cc

all: build

build:
	$(CC) rw.c -o rw `pkg-config --cflags --libs sdl3`
	./rw

clean:
	rm rw

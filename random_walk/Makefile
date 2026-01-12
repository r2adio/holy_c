CC=cc

all: build run

build:
	$(CC) rw.c -o rw `pkg-config --cflags --libs sdl3`
	
run:
	./rw

clean:
	rm rw

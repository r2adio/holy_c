all: build run

build:
	$(CC) rw.c -o rw `pkg-config --cflags --libs sdl3`
	
run: build
	./rw

clean:
	rm rw

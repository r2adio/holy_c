all: clean run

build:
	meson setup build
	ninja -C build -v

run: build
	./build/ascii_match

clean:
	rm -rf build/ .cache/

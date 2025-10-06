build:
	meson setup build
	ninja -C build

run: build
	./build/ascii_match

clean:
	rm -rf build/ .cache/

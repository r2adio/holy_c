CFLAGS := -Wall -std=c23 $(shell pkg-config --cflags raylib)
LDFLAGS := $(shell pkg-config --libs raylib)
TARGET = d_pendulum
SRC = main.c

.PHONY: all build run
all: build run

build: ${TARGET}
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

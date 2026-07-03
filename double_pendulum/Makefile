CC = gcc
CFLAGS = -Wall -Wextra -std=c23
RAYLIB_FLAGS = $(shell pkg-config --cflags --libs raylib)
FRAMEWORKS = -framework Cocoa -framework IOKit -framework CoreVideo

TARGET = d_pendulum
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(RAYLIB_FLAGS) $(FRAMEWORKS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean

CC = gcc
TARGET = pacific.exe

INC = -I./src -I./include
CFLAGS = -Wall -Wextra $(INC)
LDFLAGS = -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32 -lm

SRC = $(wildcard src/*.c) $(wildcard src/engine/*.c) $(wildcard src/engine/renderer/*.c) $(wildcard src/engine/win/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*.o build/engine/*.o build/engine/renderer/*.o build/engine/win/*.o $(TARGET)

run: $(TARGET)
	./$(TARGET)
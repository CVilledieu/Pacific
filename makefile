CC = gcc
TARGET = bin/pacific.exe

INC = -I./src -I./include
CFLAGS = -Wall -Wextra $(INC)
LDFLAGS = -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32 -lm

SRC = $(wildcard src/*.c) $(wildcard src/engine/*.c) $(wildcard src/engine/renderer/*.c) $(wildcard src/engine/win/*.c)
OBJ = $(patsubst src/%.c,bin/%.o,$(SRC))



all: raze $(TARGET) purge migrate

$(TARGET): $(OBJ)
	@mkdir -p bin
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

bin/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Copies necessary runtime assests into bin/
migrate: 
	@mkdir -p bin
	@cp -r assests bin/

# Ensures all old files are removed
raze:
	rm -rf bin/

# Removes compiling artifacts
purge:
	rm -rf bin/*.o bin/*/

# Compiles and runs the program for faster development
run: all
	cd bin && ./pacific.exe


.PHONY: all raze run purge migrate 
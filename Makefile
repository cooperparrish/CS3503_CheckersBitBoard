# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = checkers

# Source files
SOURCES = main.c checkers.c bit_functions.c
HEADERS = checkers.h bit_functions.h
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the game
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run

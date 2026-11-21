
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

# Executable name
TARGET = apc

# Source files
SRCS = main.c apc.c add.c sub.c mul.c div.c display.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compile source files
%.o: %.c apc.h
	$(CC) $(CFLAGS) -c $< -o $@

# Remove generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Clean and build again
rebuild: clean all

.PHONY: all clean rebuild

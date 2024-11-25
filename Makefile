# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Target executable
TARGET = project3

# Source and object files
SRCS = project3.c algos.c
OBJS = project3.o algos.o

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile project3.c into project3.o
project3.o: project3.c algos.h
	$(CC) $(CFLAGS) -c project3.c

# Rule to compile algos.c into algos.o
algos.o: algos.c algos.h
	$(CC) $(CFLAGS) -c algos.c

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)

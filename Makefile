# Makefile

# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Name of the executable
EXEC = unitTest

# Object files
OBJS = unitTest.o list.o

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Compile unitTest.c
unitTest.o: unitTest.c list.h
	$(CC) $(CFLAGS) -c unitTest.c

# Compile list.c
list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

# Clean up
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean

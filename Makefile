# Compiler to use
CC=gcc

# Compiler flags, e.g. -g for debug, -Wall for all warnings
CFLAGS=-Wall

# Name of the unit test executable
UNITTEST=unitTest

# Build the unit tests
all: $(UNITTEST)

# Link the unit test executable
$(UNITTEST): list.o unitTest.o
	$(CC) $(CFLAGS) -o $(UNITTEST) list.o unitTest.o

# Compile list source file to object file
list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

# Compile unittest source file to object file
unitTest.o: unitTest.c list.h
	$(CC) $(CFLAGS) -c unitTest.c

# Clean up build artifacts
clean:
	rm -f *.o $(UNITTEST)

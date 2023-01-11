#!/usr/bin/make

CC = g++
SRC = src/*.cpp
PROG = a.out

# Clean project and compile program
build: clean $(PROG)

# Clean project by removing executable
clean:
	rm -f $(PROG)

# Clean project, compile program, and run executable
run: build
	 ./$(PROG)

# Compile the program from latest soucrce
$(PROG): $(SRC)
	$(CC) $(SRC) -o $(PROG)

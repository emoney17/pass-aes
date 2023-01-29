CC = g++
SRC = *.cpp
PROG = safepass

# Clean project and compile program
build: $(PROG)

# Clean project by removing executable
clean:
	rm -f $(PROG)
	rm -rf temp

# Compile the program from latest soucrce
$(PROG): $(SRC)
	$(CC) $(SRC) -Wall -Wextra -l:libcryptopp.a -o $(PROG)

CC = g++
SRC = *.cpp
PROG = safepass

build: $(PROG)

clean:
	rm -f $(PROG)
	rm -rf temp

$(PROG): $(SRC)
	$(CC) $(SRC) -Wall -Wextra -l:libcryptopp.a -o $(PROG)

CC = g++
CFLAGS = -Wall -Wextra
SRC = *.cpp
LIBS = -l:libcryptopp.a
PROG = safepass

$(PROG): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o $(PROG)

clean:
	rm -f $(PROG)
	rm -rf temp

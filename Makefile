CC = g++
CFLAGS = -Wall -Wextra -std=c++17
SRC = *.cpp
LIBS = -l:libcryptopp.a
# PROG = safepass

all: $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o safepass

clean:
	$(RM) safepass
	rm -rf temp

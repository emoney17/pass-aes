all:
	g++ encode.cpp parse.cpp gen.cpp init.cpp main.cpp -Wall -l:libcryptopp.a -o safepass -std=c++17
clean:
	rm -rf temp
	rm -f safepass
	rm -f test

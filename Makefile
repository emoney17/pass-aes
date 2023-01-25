all:
	g++ gen.cpp init.cpp main.cpp -Wall -I ./cryptopp/ ./cryptopp/libcryptopp.a -o safepass -std=c++17
clean:
	rm -rf temp
	rm -f safepass

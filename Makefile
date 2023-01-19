all:
	g++ src/*.cpp -I ./cryptopp ./cryptopp/libcryptopp.a -o safe-pass.exe
clean:
	rm -f safe-pass.exe
	rm -f test/*
run: all
	./safe-pass.exe

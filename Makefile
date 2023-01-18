all:
	g++ src/*.cpp -I ./cryptopp ./cryptopp/libcryptopp.a -o safe-pass.exe
clean:
	rm -f safe-pass.exe
	rm -f test/pass
	rm -f test/test
run: all
	./safe-pass.exe

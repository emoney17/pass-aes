all:
	g++ *.cpp -I ./cryptopp ./cryptopp/libcryptopp.a -o safe-pass.exe
clean:
	rm -f safe-pass.exe
	rm -f pass
	rm -f key
run: all
	./safe-pass.exe

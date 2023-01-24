build:
	g++ main.cpp newUser.cpp user.cpp -Wall -I ./cryptopp ./cryptopp/libcryptopp.a -o safe-pass.exe
clean:
	rm -f safe-pass.exe
	rm -f pass
	rm -f key
run: build
	./safe-pass.exe

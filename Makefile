all:
	g++ tree.cpp encode.cpp parse.cpp gen.cpp init.cpp main.cpp -Wall -Wextra -l:libcryptopp.a -o pass -std=c++17
clean:
	rm -rf temp
	rm -f pass
	rm -f test

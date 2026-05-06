all: block blockChain main.cpp
	g++ -pedantic-errors -fdiagnostics-color=always -g  main.cpp block blockChain  -o main -lcrypto -lssl
block: block.h block.cpp
	g++ -pedantic-errors -fdiagnostics-color=always -g -c block.cpp -o block
blockChain: blockChain.h blockChain.cpp
	g++ -pedantic-errors -fdiagnostics-color=always -g -c blockChain.cpp -o blockChain
main: *.h *.cpp
	g++ -Wall -o CompilerParser.bin Main.cpp CompilerParser.cpp ParseTree.cpp Token.cpp
	./CompilerParser.bin
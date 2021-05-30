CXX = g++
CXXFLAGS = -g -Wall -Wextra -pedantic -std=c++11

all: wordHunt CTrieTest TTrieTest test

wordHunt: CTrie.o wordHuntMain.o wordHunt.o
	$(CXX) $(CXXFLAGS) $^ -o $@

CTrieTest: CTrieTest.o CTrie.o
	$(CXX) $(CXXFLAGS) $^ -o $@

TTrieTest: TTrieTest.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test: test.o CTrie.o
	$(CXX) $(CXXFLAGS) $^ -o $@
	
test.o: test.cpp CTrie.h TTrie.h TTrie.inc
	$(CXX) $(CXXFLAGS) -c $< -o $@

CTrie.o: CTrie.cpp CTrie.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

CTrieTest.o: CTrieTest.cpp CTrie.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

TTrieTest.o: TTrieTest.cpp TTrie.h TTrie.inc
	$(CXX) $(CXXFLAGS) -c $< -o $@

wordHunt.o: WordHunt.cpp WordHunt.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
	

clean:
	rm -f *.o CTrieTest TTrieTest wordHunt test

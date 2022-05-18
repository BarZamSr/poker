CXX := c++
CXXFLAGS := -std=gnu++2b -Wall

main.exe: main.cpp Rank.o Suit.o Card.o CardList.o
	${CXX} ${CXXFLAGS} main.cpp -o main.exe

%.o: %.c
	${CXX} ${CXXFLAGS} -c %< -o %@

clean:
	rm -f *.o *.exe

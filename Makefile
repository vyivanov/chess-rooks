CC=g++
FLAGS=-I./ -c -Wall -Wextra -O2 -std=c++14

all: chess

chess: main.o chess-board.o chess-rook.o
	$(CC) main.o chess-board.o chess-rook.o -o $@

main.o: main.cxx
	$(CC) $(FLAGS) main.cxx

chess-board.o: chess-board.hxx chess-board.cxx
	$(CC) $(FLAGS) chess-board.cxx

chess-rook.o: chess-rook.hxx chess-rook.cxx
	$(CC) $(FLAGS) chess-rook.cxx

clean:
	rm -rf *.o chess

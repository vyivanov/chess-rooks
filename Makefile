CC=g++
FLAGS=-I. -DDEBUG -Wall -Wextra -O2 -std=c++17

.PHONY: all
.PHONY: clean

all: chess

chess: chess.o chess-board.o chess-rook.o chess-tools.o
	$(CC) chess.o chess-board.o chess-rook.o chess-tools.o -lpthread -o $@

chess.o: chess.cxx
	$(CC) -c $(FLAGS) chess.cxx -o $@

chess-board.o: chess-board.hxx chess-board.cxx
	$(CC) -c $(FLAGS) chess-board.cxx -o $@

chess-rook.o: chess-rook.hxx chess-rook.cxx
	$(CC) -c $(FLAGS) chess-rook.cxx -o $@

chess-tools.o: chess-tools.hxx chess-tools.cxx
	$(CC) -c $(FLAGS) chess-tools.cxx -o $@

clean:
	rm -rf *.o chess

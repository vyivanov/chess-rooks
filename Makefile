# MIT License

# Copyright (c) 2021 Vladimir Yu. Ivanov

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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

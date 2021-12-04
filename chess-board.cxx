#include "chess-board.hxx"
#include <iostream>

namespace kasper {

ChessBoard::ChessBoard(const Params& cfg) noexcept: m_cfg{cfg} {
    // asserts on config
}

void ChessBoard::print() noexcept {
    std::cout << "print" << '\n';
}

void ChessBoard::play() noexcept {
    std::cout << "play" << '\n';
}

};

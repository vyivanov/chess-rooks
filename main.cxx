#include "chess-board.hxx"
#include <memory>
#include <chrono>

using chess_iface = std::unique_ptr<kasper::IChessBoard>;
using namespace std::chrono_literals;

int main() {
    const chess_iface chess = std::make_unique<kasper::ChessBoard>(
        kasper::ChessBoard::Params{
            .width     = 64   ,
            .height    = 64   ,
            .rooks_num = 5    ,
            .delay_min = 200ms,
            .delay_max = 300ms,
        }
    );
    chess->print();
    chess->play();
    chess->print();
}

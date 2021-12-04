#include "chess-board.hxx"

#include <chrono>
#include <memory>

int main()
{
    using namespace std::chrono_literals;

    const kasper::IChessBoard::Ptr chess = std::make_unique<kasper::ChessBoard>(
        kasper::IChessBoard::Cfg {
            .rows = 8,
            .cols = 8,
            .rooks_num = 6,
            .moves_num = 50,
            .delay_min = 200ms,
            .delay_max = 300ms,
        }
    );

    chess->show();
    chess->play();
    chess->show();
}

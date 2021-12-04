#pragma once

// #include "chess-rook.hxx"

#include <cstdint>
#include <chrono>
#include <mutex>
#include <vector>

namespace kasper {

using milliseconds = std::chrono::milliseconds;

class IChessBoard {
public:
    virtual void print() noexcept = 0;
    virtual void play()  noexcept = 0;
};

class ChessBoard final: public IChessBoard {
public:
    struct Params {
        std::uint8_t width;
        std::uint8_t height;
        std::uint8_t rooks_num;
        milliseconds delay_min;
        milliseconds delay_max;
    };
    explicit ChessBoard(const Params& cfg) noexcept;
    ChessBoard(const ChessBoard& other) = delete;
    ChessBoard(ChessBoard&& other) = delete;
    ChessBoard& operator=(const ChessBoard& other) = delete;
    ChessBoard& operator=(ChessBoard&& other) = delete;
    void print() noexcept override;
    void play()  noexcept override;
private:
    const Params m_cfg;
    std::mutex   m_freezer;
    // std::vector<IChessRook> m_rooks;
};

};


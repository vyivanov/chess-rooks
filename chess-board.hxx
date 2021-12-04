#pragma once

#include "chess-tools.hxx"
#include "chess-rook.hxx"

#include <memory>
#include <cstdint>
#include <vector>
#include <unordered_set>

namespace kasper {

class IChessBoard {
public:
    using Ptr = std::unique_ptr<IChessBoard>;
public:
    struct Cfg {
        std::uint8_t rows;
        std::uint8_t cols;
        std::uint8_t rooks_num;
        std::uint8_t moves_num;
        Milliseconds delay_min;
        Milliseconds delay_max;
    };
public:
    virtual void show() const noexcept = 0;
    virtual void play()       noexcept = 0;
public:
    IChessBoard()                                    = default;
    virtual ~IChessBoard()                           = default;
    IChessBoard(const IChessBoard& other)            = delete;
    IChessBoard(IChessBoard&& other)                 = delete;
    IChessBoard& operator=(const IChessBoard& other) = delete;
    IChessBoard& operator=(IChessBoard&& other)      = delete;
protected:
    using Matrix    = std::vector<char>;
    using HashTable = std::unordered_set<std::uint16_t>;
};

class ChessBoard final: public IChessBoard {
public:
    explicit ChessBoard(const IChessBoard::Cfg& config) noexcept;
public:
    void show() const noexcept override;
    void play()       noexcept override;
private:
    TypeGuard<IChessRook::List>::Ptr populate()   const noexcept;
    void print(const IChessBoard::Matrix& matrix) const noexcept;
private:
    const IChessBoard::Cfg                 m_config;
    const TypeGuard<IChessRook::List>::Ptr m_rooks;
};

};

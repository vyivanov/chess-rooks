// MIT License

// Copyright (c) 2021 Vladimir Yu. Ivanov

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
    void assert_poses() const noexcept;
private:
    const IChessBoard::Cfg                 m_config;
    const TypeGuard<IChessRook::List>::Ptr m_rooks;
};

};

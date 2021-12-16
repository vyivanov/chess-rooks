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

#include "chess-board.hxx"
#include "chess-rook.hxx"
#include "chess-tools.hxx"

#include <chrono>
#include <cassert>
#include <cstdio>
#include <memory>
#include <utility>
#include <iostream>

using namespace std::chrono_literals;

namespace kasper {

ChessBoard::ChessBoard(const IChessBoard::Cfg& config) noexcept
    : m_config(config)
    , m_rooks(populate())
{
    assert(0 < m_config.rows and m_config.rows < (16+1)            and "check client config");
    assert(0 < m_config.cols and m_config.cols < (16+1)            and "check client config");
    assert(0 < m_config.rooks_num and m_config.rooks_num < (9+1)   and "check client config");
    assert(0 < m_config.moves_num and m_config.moves_num < (200+1) and "check client config");
    assert(m_config.rows == m_config.cols                          and "check client config");
    assert(m_config.rooks_num <= config.rows * config.cols         and "check client config");
    assert(m_config.delay_min <= m_config.delay_max                and "check client config");
    assert(1ms <= m_config.delay_min and m_config.delay_min <= 1s  and "check client config");
    assert(1ms <= m_config.delay_max and m_config.delay_max <= 1s  and "check client config");
    assert(m_config.rooks_num == m_rooks->obj().size()             and "check populate logic");
}

void ChessBoard::show() const noexcept   /* T = O(rows*cols) */
{
    auto matrix = IChessBoard::Matrix(m_config.rows * m_config.cols, '-');

    for (const IChessRook::Ptr& rook: m_rooks->obj())
    {
        const IChessRook::Index idx = rook->get_index();
        const IChessRook::Pose  pos = rook->get_position();

        matrix.at(pos.row * m_config.rows + pos.col) = '0' + idx;

        std::printf("rook_%d: (%d,%d)\n", idx, pos.row, pos.col);
    }

    print(matrix);
}

void ChessBoard::play() noexcept   /* T = O(rooks_num**2) */
{
    assert_poses();

    for (const IChessRook::Ptr& rook: m_rooks->obj())
    {
        rook->move();
    }

    for (const IChessRook::Ptr& rook: m_rooks->obj())
    {
        rook->wait();
    }

    assert_poses();
}

TypeGuard<IChessRook::List>::Ptr ChessBoard::populate() const noexcept   /* T = O(rooks_num) */
{
    TypeGuard<IChessRook::List>::Ptr neighbors = std::make_shared<TypeGuard<IChessRook::List>>();

    const decltype(m_config.rows) lim_row = m_config.rows - 1;
    const decltype(m_config.cols) lim_col = m_config.cols - 1;

    auto known_poses = IChessBoard::HashTable{};

    for (IChessRook::Index idx = 0; idx < m_config.rooks_num; ++idx)
    {
        bool is_choose_pose = true;

        while (is_choose_pose)
        {
            const auto pos_row = RandGen(0, lim_row).uniform();
            const auto pos_col = RandGen(0, lim_col).uniform();

            const auto [_, ok] = known_poses.insert(pos_row * 1'024U + pos_col);

            if (ok)
            {
                is_choose_pose = false;
            }
            else
            {
                continue;
            }

            const auto pos = IChessRook::Pose{.row = pos_row, .col = pos_col};
            const auto lim = IChessRook::Pose{.row = lim_row, .col = lim_col};

            IChessRook::Ptr rook = std::make_unique<ChessRook>(
                IChessRook::Cfg {
                    .index     = idx,
                    .init      = pos,
                    .limit     = lim,
                    .moves_num = m_config.moves_num,
                    .delay_min = m_config.delay_min,
                    .delay_max = m_config.delay_max,
                },
                neighbors
            );

            neighbors->obj().push_back(std::move(rook));
        }
    }

    return neighbors;
}

void ChessBoard::print(const IChessBoard::Matrix& matrix) const noexcept   /* T = O(rows*cols) */
{
    std::cout << '\n';

    for (auto row = 0; row < m_config.rows; ++row)
    {
        for (auto col = 0; col < m_config.cols; ++col)
        {
            const auto idx = row * m_config.rows + col;
            std::cout << matrix.at(idx);
            (idx + 1) % m_config.cols ? std::cout << '\x20' : std::cout << '\n';
        }
    }

    std::cout << '\n';
    std::cout.flush();
}

void ChessBoard::assert_poses() const noexcept
{
#ifdef DEBUG
    auto known_poses = IChessBoard::HashTable{};

    for (const IChessRook::Ptr& rook: m_rooks->obj())
    {
        const IChessRook::Pose pose = rook->get_position();
        const auto [_, ok] = known_poses.insert(pose.row * 1'024U + pose.col);
        if (not ok)
        {
            assert(false and "rooks collision detected");
        }
    }
#endif
}

};

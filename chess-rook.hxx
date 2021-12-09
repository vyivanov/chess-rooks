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

#include <cstdint>
#include <memory>
#include <vector>
#include <atomic>
#include <thread>

namespace kasper {

class IChessRook {
public:
    using Index = std::uint8_t;
    using Ptr   = std::unique_ptr<IChessRook>;
    using List  = std::vector<IChessRook::Ptr>;
public:
    struct Pose {
        std::uint16_t row;
        std::uint16_t col;
        bool operator==(const Pose& other) const noexcept;
        bool operator!=(const Pose& other) const noexcept;
    };
    struct Cfg {
        Index index;
        Pose  init;
        Pose  limit;
        std::uint8_t moves_num;
        Milliseconds delay_min;
        Milliseconds delay_max;
    };
public:
    virtual Index get_index()    const noexcept = 0;
    virtual Pose  get_position() const noexcept = 0;
public:
    virtual void move() noexcept = 0;
    virtual void wait() noexcept = 0;
public:
    IChessRook()                                   = default;
    virtual ~IChessRook()                          = default;
    IChessRook(const IChessRook& other)            = delete;
    IChessRook(IChessRook&& other)                 = delete;
    IChessRook& operator=(const IChessRook& other) = delete;
    IChessRook& operator=(IChessRook&& other)      = delete;
protected:
    enum class MoveVector {
        UP, DOWN, LEFT, RIGHT
    };
};

class ChessRook final: public IChessRook {
public:
    ChessRook(const IChessRook::Cfg& config, TypeGuard<IChessRook::List>::Ptr neighbors) noexcept;
public:
    IChessRook::Index get_index()    const noexcept override { return m_index;    };
    IChessRook::Pose  get_position() const noexcept override { return m_position; };
public:
    void move() noexcept override { m_spinlock.store(false); };
    void wait() noexcept override { m_worker.join();         };
private:
    void worker() noexcept;
private:
    IChessRook::Pose new_position() const noexcept;
    IChessRook::MoveVector cmp_position(const IChessRook::Pose& new_pose) const noexcept;
    bool is_move_to(const IChessRook::Pose& new_pose) const noexcept;
private:
    IChessRook::Index const m_index;
    IChessRook::Pose        m_position;
    IChessRook::Pose  const m_limitation;
    std::uint8_t      const m_moves_num;
    std::uint8_t            m_moves_cnt;
    Milliseconds      const m_delay_min;
    Milliseconds      const m_delay_max;
    TypeGuard<IChessRook::List>::Ptr const m_neighbors;
    std::atomic<bool>       m_spinlock;
    std::thread             m_worker;
};

};

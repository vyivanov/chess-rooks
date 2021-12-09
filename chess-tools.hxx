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

#include <chrono>
#include <memory>
#include <mutex>
#include <cstdint>
#include <random>

namespace kasper {

using Milliseconds = std::chrono::milliseconds;

template<typename T>
class TypeGuard final {
public:
    using Ptr = std::shared_ptr<TypeGuard<T>>;
public:
    T&          obj() noexcept { return m_obj; }
    std::mutex& mtx() noexcept { return m_mtx; }
private:
    T          m_obj;
    std::mutex m_mtx;
};

class RandGen final {
public:
    explicit RandGen(std::uint16_t from = 0U, std::uint16_t to = 1U, float prob = 0.5F) noexcept;
public:
    std::uint16_t uniform()   noexcept;
    bool          bernoulli() noexcept;
private:
    std::uint16_t const m_from;
    std::uint16_t const m_to;
    float         const m_prob;
    std::random_device  m_dev;
    std::mt19937        m_gen;
};

};

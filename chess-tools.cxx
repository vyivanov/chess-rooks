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

#include "chess-tools.hxx"

#include <cstdint>
#include <cassert>
#include <random>

namespace kasper {

RandGen::RandGen(const std::uint16_t from, const std::uint16_t to, const float prob) noexcept
    : m_from(from)
    , m_to(to)
    , m_prob(prob)
    , m_dev()
    , m_gen(m_dev())
{
    assert(m_from <= m_to                    and "check client config");
    assert(0.1F <= m_prob and m_prob <= 1.0F and "check client config");
}

std::uint16_t RandGen::uniform() noexcept
{
    return std::uniform_int_distribution<>(m_from, m_to)(m_gen);
}

bool RandGen::bernoulli() noexcept
{
    return std::bernoulli_distribution(m_prob)(m_gen);
}

};

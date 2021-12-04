#include "chess-tools.hxx"

#include <cstdint>
#include <cassert>
#include <random>

namespace kasper {

RandGen::RandGen(const std::uint16_t from, const std::uint16_t to, const float prob) noexcept
    : m_from{from}
    , m_to{to}
    , m_prob{prob}
    , m_dev{}
    , m_gen{m_dev()}
{
    assert(m_from <= m_to and "check client config");
    assert(m_prob > 0.1F  and "check client config");
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

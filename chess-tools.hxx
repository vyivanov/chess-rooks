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

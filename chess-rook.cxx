#include "chess-rook.hxx"
#include "chess-tools.hxx"

#include <utility>
#include <thread>
#include <cassert>
#include <mutex>

namespace kasper {

ChessRook::ChessRook(const IChessRook::Cfg& config, TypeGuard<IChessRook::List>::Ptr neighbors) noexcept
    : m_index(config.index)
    , m_position(config.init)
    , m_limitation(config.limit)
    , m_moves_num(config.moves_num)
    , m_moves_cnt(0)
    , m_delay_min(config.delay_min)
    , m_delay_max(config.delay_max)
    , m_neighbors(std::move(neighbors))
    , m_spinlock(true)
    , m_worker(std::thread(&ChessRook::worker, this))
{
    assert(m_moves_cnt == 0    and "check ctor");
    assert(m_spinlock.load()   and "check ctor");
    assert(m_worker.joinable() and "check ctor");
}

void ChessRook::worker() noexcept
{
    RandGen rand_delay(m_delay_min.count(), m_delay_max.count());

    while (m_spinlock.load()) {;;;;;}
    while (true)
    {
        {
            const std::lock_guard<std::mutex> lock(m_neighbors->mtx());

            const auto new_pose = new_position();
            const auto is_move  = is_move_to(new_pose);

            if (not is_move or (m_moves_cnt > m_moves_num - 1))
            {
                break;
            }

            m_position = new_pose;
            m_moves_cnt++;
        }

        std::this_thread::sleep_for(Milliseconds(rand_delay.uniform()));
    }
}

IChessRook::Pose ChessRook::new_position() const noexcept
{
    const bool is_move_row = RandGen().bernoulli();

    IChessRook::Pose new_pose = m_position;

    if (is_move_row)
    {
        new_pose.row = RandGen(0, m_limitation.row).uniform();
    }
    else
    {
        new_pose.col = RandGen(0, m_limitation.col).uniform();
    }

    assert(
    (
        (new_pose.row != m_position.row and new_pose.col == m_position.col) or
        (new_pose.col != m_position.col and new_pose.row == m_position.row) or (new_pose == m_position)
    )
        and "the rook is allowed to be moved only (1) vertically or (2) horizontally or (3) to be stationary"
    );

    return new_pose;
}

IChessRook::MoveVector ChessRook::cmp_position(const IChessRook::Pose& new_pose) const noexcept
{
    if (new_pose == m_position)
    {
        return IChessRook::MoveVector::ZERO;
    }

    if (new_pose.row != m_position.row)
    {
        return (new_pose.row < m_position.row) ? IChessRook::MoveVector::UP : IChessRook::MoveVector::DOWN;
    }

    if (new_pose.col != m_position.col)
    {
        return (new_pose.col < m_position.col) ? IChessRook::MoveVector::LEFT : IChessRook::MoveVector::RIGHT;
    }

    assert(false and "check method logic");
}

bool ChessRook::is_move_to(const IChessRook::Pose& new_pose) const noexcept
{
    const auto move_vector = cmp_position(new_pose);

    bool is_move = true;

    if (IChessRook::MoveVector::ZERO == move_vector)
    {
        return is_move;
    }

    for (const IChessRook::Ptr& rook: m_neighbors->obj())
    {
        if (rook->get_index() == m_index)
        {
            continue;
        }

        const auto neighbor = rook->get_position();

        if (IChessRook::MoveVector::UP == move_vector)
        {
            is_move &= not (
                (neighbor.col == m_position.col) and (new_pose.row <= neighbor.row) and (neighbor.row < m_position.row)
            );
        }
        else if (IChessRook::MoveVector::DOWN == move_vector)
        {
            is_move &= not (
                (neighbor.col == m_position.col) and (m_position.row < neighbor.row) and (neighbor.row <= new_pose.row)
            );
        }
        else if (IChessRook::MoveVector::LEFT == move_vector)
        {
            is_move &= not (
                (neighbor.row == m_position.row) and (new_pose.col <= neighbor.col) and (neighbor.col < m_position.col)
            );
        }
        else if (IChessRook::MoveVector::RIGHT == move_vector)
        {
            is_move &= not (
                (neighbor.row == m_position.row) and (m_position.col < neighbor.col) and (neighbor.col <= new_pose.col)
            );
        }
        else
        {
            assert(false and "check method logic");
        }
    }

    return is_move;
}

bool IChessRook::Pose::operator==(const IChessRook::Pose& other) const noexcept
{
    return (row == other.row) and (col == other.col);
}

};

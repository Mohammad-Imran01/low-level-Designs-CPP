#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <vector>
#include <thread>
#include <functional>
#include <utility> // Required for std::forward

class ThreadPool
{
public:
    ThreadPool(size_t maxThreads);
    ~ThreadPool();

    // ⛔️ Delete copy and move operations to ensure thread safety
    // The ThreadPool manages threads and locks, which should not be copied or moved.
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &&) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;

    /**
     * @brief Enqueues a new task for execution.
     * @tparam T A callable type (function, lambda, std::bind result, etc.).
     * @param t The task to enqueue.
     */
    template <typename T>
    void enqueue(T &&t);

private:
    std::mutex m_mtx;
    std::vector<std::thread> m_threads;
    std::queue<std::function<void()>> m_tasks;
    std::condition_variable m_cv;
    bool m_KeepRunning;
};

// Template definition must be in the header file or a separate implementation file
// if not using a single-file approach. For simplicity, it's often placed here.
template <typename T>
void ThreadPool::enqueue(T &&t)
{
    std::unique_lock locker(m_mtx);
    m_tasks.emplace(std::forward<T>(t));

    m_cv.notify_one();
}
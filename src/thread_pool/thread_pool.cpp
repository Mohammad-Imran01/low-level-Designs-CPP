#include "thread_pool.h"

#include <utility>

ThreadPool::ThreadPool(size_t maxThreads)
    : m_KeepRunning(true)
{
    for (size_t i = 0; i < maxThreads; ++i)
    {
        auto threadFunc = [this]()
        {
            while (true)
            {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(m_mtx);

                    // CRITICAL FIX: The predicate should be 'stop OR not empty'
                    // Wait will block until one of these is true.
                    m_cv.wait(lock, [this]
                              { return !m_KeepRunning || !m_tasks.empty(); });

                    // Check for termination condition *after* waking up
                    if (!m_KeepRunning && m_tasks.empty())
                        return; // Exit the thread function

                    task = std::move(m_tasks.front());
                    m_tasks.pop();
                } // Lock released automatically here (unique_lock)

                task();
            }
        };

        m_threads.emplace_back(std::move(threadFunc));
    }
}

ThreadPool::~ThreadPool()
{

    std::unique_lock locker(m_mtx);
    m_KeepRunning = false;
    locker.unlock();

    m_cv.notify_all(); // Wake up ALL waiting threads

    for (auto &thread : m_threads)
    {
        if (thread.joinable())
            thread.join();
    }
}
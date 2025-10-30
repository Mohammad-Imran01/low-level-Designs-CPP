#include <iostream>
#include <sstream>
#include <thread> // Added for std::this_thread::sleep_for
#include <chrono> // Added for std::chrono::milliseconds

#include "constants.h"
#include "logger.h"
#include "thread_pool.h"

int main()
{
    // C++ thread IDs are not easily printable as integers by default,
    // so we define a lambda to safely convert the ID to a string.
    auto threadStringId = []() -> std::string
    {
        std::stringstream ss;
        ss << std::this_thread::get_id();
        return ss.str();
    };

    std::cout << "\n--- Demonstration Starts ---\n";

    std::cout << "---- ******************** ----\n";
    std::cout << "--- ****** Logger ******** ---\n";
    std::cout << "---- ******************** ----\n";
    
    // Use the thread-safe singleton Logger
    auto &lg = Logger::instance();

    const std::filesystem::path logFilePath = Im::CONST_DIR_APP_FILE;

    std::cout << "Attempting to set log file to: " << logFilePath.string() << std::endl;

    // 3. Set the log file. This will create directories and the file if needed.
    lg.setLogFile(logFilePath.string());

    lg.info("Application started successfully.");
    lg.warning("Configuration file not found, using defaults.");

    lg.error("A critical system component failed to initialize.");
    lg.info("Program running, checking status...");

    std::cout << "---- ******************** ----\n";
    std::cout << "--- ****** Thread Pool ******* ---\n";
    std::cout << "---- ******************** ----\n";

    // Create the thread pool with 5 worker threads
    ThreadPool threadPool(5);

    // Enqueue 20 tasks
    for (int i = 0; i < 20; ++i)
    {
        threadPool.enqueue(
            // The lambda captures the logger, task ID (i), and the ID function
            [&lg, i, threadStringId]()
            {
                // Task: Report start, simulate work, report finish
                std::string current_thread_id = threadStringId();
                
                // Log start
                lg.info("Task #" + std::to_string(i) + " STARTING on Thread ID: " + current_thread_id);

                // Simulate some computation/IO-bound work
                std::this_thread::sleep_for(std::chrono::milliseconds(50));

                // Log finish
                lg.info("Task #" + std::to_string(i) + " FINISHED on Thread ID: " + current_thread_id);
            });
    }

    // Wait for a sufficient amount of time (e.g., 2.5 seconds, as tasks are 50ms each)
    // for most tasks to run before the ThreadPool destructor is called.
    std::cout << "Main thread waiting for 2.5 seconds for tasks to complete...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    
    // The ThreadPool destructor will be called automatically here, 
    // joining all remaining running threads and ensuring a graceful shutdown.

    std::cout << "\n--- End of Demonstration ---\n";

    return 0;
}
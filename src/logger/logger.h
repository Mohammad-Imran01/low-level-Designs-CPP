#pragma once

#include <string>
#include <fstream>
#include <memory>
#include <mutex>

class Logger
{
public:
    // Singleton access method (Meyers Singleton)
    static Logger &instance();

    // Deleted copy constructor and assignment operator to enforce Singleton
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    // Public API for logging
    void info(const std::string &message);
    void warning(const std::string &message);
    void error(const std::string &message);

    // Setup function for the log file
    void setLogFile(const std::string &fileLocation);

private:
    // Log priority levels
    enum class Priority { INFO, WARNING, ERROR };

    // Private constructor and destructor
    Logger();
    ~Logger();

    // The thread-safe logging function
    void log(Priority level, const std::string &message);

    // Utility functions
    std::string logLevelString(Priority priority);
    std::string timestamp() const;

private: 
    std::mutex fileMutex; 
    std::unique_ptr<std::fstream> m_file; 
};
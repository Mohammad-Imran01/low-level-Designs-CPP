#pragma once

#include <memory>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <mutex>
#include <fstream>

class Logger
{

public:
    enum Priority
    {
        INFO,
        WARNING,
        ERROR
    };

    static Logger &instance();
    void setLogFile(const std::string &fileLocation);
    void log(Priority level, const std::string &message);

    void info(const std::string &message);
    void warning(const std::string &message);
    void error(const std::string &message);

    ~Logger();
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

private:
    Logger();
    std::mutex fileMutex;
    std::unique_ptr<std::fstream> m_file;

    std::string logLevelString(Priority);
    std::string timestamp() const;
};
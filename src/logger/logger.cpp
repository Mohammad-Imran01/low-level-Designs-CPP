#include "logger.h"

#include <iomanip>
#include <chrono>

Logger &Logger::instance()
{
    static Logger inst;
    return inst;
}

Logger::Logger()
{
    // You can initialize anything here if needed
    std::cout << "Logger initialized.\n";
}

Logger::~Logger()
{
    std::scoped_lock locker(fileMutex);
    if (m_file && m_file->is_open())
    {
        m_file->close();
    }
    std::cout << "\nLogger destroyed!";
}

void Logger::setLogFile(const std::string &fileLocation)
{
    std::scoped_lock locker(fileMutex);

    if (m_file && m_file->is_open())
        m_file->close();

    m_file = std::make_unique<std::fstream>(fileLocation, std::ios::out | std::ios::app);
    if (!m_file || !m_file->is_open())
    {
        std::ofstream create(fileLocation);
        create.close();
        m_file = std::make_unique<std::fstream>(fileLocation, std::ios::out | std::ios::app);
    }

    if (!m_file->is_open())
        throw std::runtime_error("Failed to open/create the log file. " + fileLocation);
}
void Logger::log(Priority level, const std::string &message)
{
    std::string toLog =
        "[" + timestamp() + "] [" + logLevelString(level) + "] " + message + "\n";

    std::scoped_lock locker(fileMutex);
    std::cout << toLog;

    if (m_file && m_file->is_open())
    {
        *m_file << toLog;
        m_file->flush();
    }
    else
    {
        std::cerr << "Log file not open.\n";
    }
}

void Logger::info(const std::string &message)
{
    log(Priority::INFO, message);
}
void Logger::warning(const std::string &message)
{
    log(Priority::WARNING, message);
}
void Logger::error(const std::string &message)
{
    log(Priority::ERROR, message);
}
std::string Logger::logLevelString(Priority priority)
{
    switch (priority)
    {
    case Priority::INFO:
        return "INFO";
    case Priority::WARNING:
        return "WARNING";
    case Priority::ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

std::string Logger::timestamp() const
{
    //     auto now = std::chrono::system_clock::now();
    //     std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    //     std::tm tm{};
    // #ifdef _WIN32
    //     localtime_s(&tm, &now_c);
    // #else
    //     localtime_r(&now_c, &tm);
    // #endif
    //     std::ostringstream oss;
    //     oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    //     return oss.str();

    static const char *FORMAT = "YYYY-MM-DD HH:MM:SS";
    std::time_t timer = std::time({});
    char buf[30];
    if (std::strftime(buf, sizeof(buf), FORMAT, std::localtime(&timer)));
    return buf;
    return FORMAT;
}
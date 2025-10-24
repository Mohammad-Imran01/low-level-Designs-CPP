#include "logger.h"

static Logger &Logger::instance()
{
    static Logger log;
    return log;
}
void Logger::setLogFile(const std::string &fileLocation)
{
}
void Logger::log(Priority level, const std::string &message)
{
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
    if (priority == Priority::ERROR)
        return "ERROR";
    else if (priority == Priority::INFO)
        return "INFO";
    else
        return "Warning";
}
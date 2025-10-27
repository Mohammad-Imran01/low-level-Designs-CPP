#include "logger.h"

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <iomanip>
 

Logger &Logger::instance()
{ 
    static Logger inst;
    return inst;
}
 

Logger::Logger()
{
    std::cout << "Logger initialized.\n";
}

Logger::~Logger()
{
    // Close the file stream safely
    std::scoped_lock locker(fileMutex);
    if (m_file && m_file->is_open())
    {
        m_file->close();
    }
    std::cout << "\nLogger destroyed!\n";
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
    static const char *FORMAT = "%Y-%m-%d %H:%M:%S"; 

    std::time_t timer = std::time({});
    char buf[30];
 
    if (std::strftime(buf, sizeof(buf), FORMAT, std::localtime(&timer)))
        return buf;

    return "[TIME_ERROR]";
}
 

void Logger::setLogFile(const std::string &fileLocation)
{
    std::filesystem::path filePath(fileLocation);
    std::scoped_lock locker(fileMutex);

    try
    { 
        std::filesystem::path parentDir = filePath.parent_path();
        if (!parentDir.empty())
        { 
            std::filesystem::create_directories(parentDir); 
        }
 
        if (m_file && m_file->is_open())
            m_file->close();

        // Open the file in append mode. This will create it if it doesn't exist.
        m_file = std::make_unique<std::fstream>(filePath, std::ios::out | std::ios::app);

        // 4. Check for success
        if (!m_file || !m_file->is_open())
        { 
            std::cerr << "ERROR: Failed to open log file '" << fileLocation
                      << "'. Logging to file is disabled." << std::endl;
            
            // Set unique_ptr to null, preventing future attempts to write to it
            m_file.reset(); 
        }
    }
    catch (const std::exception &e)
    { 
        std::cerr << "ERROR: Exception during log file setup for '" << fileLocation
                  << "'. Reason: " << e.what() << std::endl;
        m_file.reset();
    }
    catch (...)
    {
        std::cerr << "ERROR: Unknown exception during log file setup for '" << fileLocation << "'" << std::endl;
        m_file.reset();
    }
}
 

void Logger::log(Priority level, const std::string &message)
{ 
    std::string toLog =
        "[" + timestamp() + "] [" + logLevelString(level) + "] " + message + "\n";

     std::scoped_lock locker(fileMutex);
    
    // Always print to console
    std::cout << toLog;

    if (m_file && m_file->is_open())
    {
        // Write to file
        *m_file << toLog;
 
        if (level == Priority::ERROR)
        {
            m_file->flush();
        }
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

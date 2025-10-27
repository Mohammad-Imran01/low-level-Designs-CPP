#pragma once

#include <string>
#include <filesystem>
#include <cstdlib>

namespace Im
{
    /**
     * @brief Gets the user's home directory path, handling Windows and POSIX systems.
     * @return std::filesystem::path The path to the user's home directory, or '.' as a fallback.
     */
    inline std::filesystem::path getUserHome()
    {
        const char *homeDir = nullptr;
#ifdef _WIN32
        // Windows uses USERPROFILE
        homeDir = std::getenv("USERPROFILE");
#else
        // Linux/macOS use HOME
        homeDir = std::getenv("HOME");
#endif
        if (!homeDir)
            homeDir = "."; // fallback to current directory

        return std::filesystem::path(homeDir);
    }

    /**
     * @brief Defines the full path for the log file, using a cross-platform approach.
     * Path: ~/Downloads/LoggerTemp/log.txt
     */
    static const std::filesystem::path CONST_DIR_APP_FILE =
        getUserHome() / "Downloads" / "LoggerTemp" / "log.txt";
}
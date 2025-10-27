#pragma once

#include <string>
#include <filesystem>
#include <cstdlib>

namespace Im
{

        inline std::filesystem::path getUserHome()
        {
                const char *homeDir = nullptr;
#ifdef _WIN32
                homeDir = std::getenv("USERPROFILE");
#else
                homeDir = std::getenv("HOME");
#endif
                if (!homeDir)
                        homeDir = ".";

                return std::filesystem::path(homeDir);
        }

        static const std::filesystem::path CONST_DIR_APP_FILE =
            getUserHome() / "Downloads" / "LoggerTemp" / "log.txt";
}
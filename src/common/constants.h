#include <string>
#include <filesystem>
#include <cstdlib>

namespace Im
{
    static const std::filesystem::path CONST_DIR_APP_FILE = std::filesystem::path(
                                                                std::getenv("USERPROFILE")) /
                                                            "Downloads" / "LoggerTemp" / "log.txt";
}
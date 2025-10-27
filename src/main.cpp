#include <iostream>

#include "./logger/logger.h"
#include "constants.h"

int main()
{
    std::cout << "\n\n"
              << std::endl;

    std::cout << "Hello, Guys!" << std::endl;

    auto &lg = Logger::instance();
    lg.setLogFile((Im::CONST_DIR_APP_FILE).string());

    lg.info("This code works");
    lg.error("This code works");
    lg.warning("This code works");

    std::cout << "\n\n"
              << std::endl;
    return 0;
}

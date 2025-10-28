#include <iostream>
#include "constants.h"
#include "logger.h"

int main()
{
    // std::cout << "--- Logger Demonstration ---\n"
    //           << std::endl;

    // 1. Get the Logger instance
    auto &lg = Logger::instance();

    // 2. Determine the log file location using the constant path
    const std::filesystem::path logFilePath = Im::CONST_DIR_APP_FILE;

    std::cout << "Attempting to set log file to: " << logFilePath.string() << std::endl;

    // 3. Set the log file. This will create directories and the file if needed.
    lg.setLogFile(logFilePath.string());

    // 4. Log various messages
    lg.info("Application started successfully.");
    lg.warning("Configuration file not found, using defaults.");

    // An error log should flush immediately to disk
    lg.error("A critical system component failed to initialize.");
    lg.info("Program running, checking status...");

    std::cout << "\n--- End of Demonstration ---\n";
    std::cout << "Check the file: " << logFilePath.string() << " to see the output." << std::endl;

    // Logger destructor called automatically upon exiting main()
    return 0;
}

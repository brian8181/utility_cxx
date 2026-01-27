// ConsoleLogger.h/cpp
#include <iostream>
#include "ILogger.h"

class ConsoleLogger : public ILogger {
public:
    void log_info(const char* message) override {
        std::cout << "[INFO] " << message << std::endl;
    }

    void log_error(const char* message) override {
        std::cerr << "[ERROR] " << message << std::endl;
    }
};

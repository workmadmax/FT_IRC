#pragma once

class Debug {
public:
    void info(const std::string &msg) {
        std::cout << "[INFO] " << msg << std::endl;
    }

    void error(const std::string &msg) {
        std::cerr << "[ERROR] " << msg << std::endl;
    }
};

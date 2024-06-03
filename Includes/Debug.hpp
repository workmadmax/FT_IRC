#pragma once

#include "libs.hpp"

class Debug {
public:
    void    exit_with_error(const std::string &msg) {
        std::cerr << msg;
        exit(EXIT_FAILURE);
    }
    void    ft_info(const std::string &msg) {
        std::cout << msg;
    }
    void    ft_error(const std::string &msg) {
        std::cerr << msg;
    }
};

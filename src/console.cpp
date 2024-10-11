// console.cpp
#include "console.hpp"
#include <iostream>

void Console::showCursor(bool show_flag) {
    if (show_flag) {
        // Show cursor
        std::cout << "\e[?25h";
    } else {
        // Hide cursor
        std::cout << "\e[?25l";
    }
}

void Console::clearLine() {
    // Clear the current line
    std::cout << "\r\33[2K";
}

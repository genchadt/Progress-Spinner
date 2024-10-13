#include "progress_spinner/iconsole.hpp"

#ifdef _WIN32

WindowsConsole::WindowsConsole() {
    setUTF8();
    enableANSISupport();
}

void WindowsConsole::showCursor(bool show_flag) const {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(out, &cursor_info);
    cursor_info.bVisible = show_flag;
    SetConsoleCursorInfo(out, &cursor_info);
}

void WindowsConsole::setUTF8() const {
    SetConsoleOutputCP(CP_UTF8);
}

void WindowsConsole::enableANSISupport() const {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(out, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(out, mode);
}

#else

void UnixConsole::showCursor(bool show_flag) const {
    std::cout << (show_flag ? "\033[?25h" : "\033[?25l");
}

#endif

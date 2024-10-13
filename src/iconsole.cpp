#include "progress_spinner/iconsole.hpp"

#ifdef _WIN32

/**
 * \brief Constructor for WindowsConsole
 *
 * Enables UTF-8 output and ANSI escape sequences in the console.
 */
WindowsConsole::WindowsConsole() {
    setUTF8();
    enableANSISupport();
}

/**
 * \brief Set the console cursor visibility to the given flag.
 *
 * This function manipulates the console's cursor visibility using the Windows API.
 * It retrieves the current console cursor information, sets the visibility to the
 * given flag, and then sets the information back to the console.
 *
 * \param[in] show_flag true to show the cursor, false to hide it.
 */
void WindowsConsole::showCursor(bool show_flag) const {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(out, &cursor_info);
    cursor_info.bVisible = show_flag;
    SetConsoleCursorInfo(out, &cursor_info);
}

/**
 * \brief Sets the console output code page to UTF-8.
 *
 * This function sets the console output to use the UTF-8 character encoding.
 * This is required for proper display of Unicode characters in the console.
 */
void WindowsConsole::setUTF8() const {
    SetConsoleOutputCP(CP_UTF8);
}

/**
 * \brief Enable ANSI escape sequences for the console.
 *
 * This function enables the support for ANSI escape sequences in the console.
 * This is required for the proper display of colors and other decorations
 * that rely on ANSI escape sequences.
 */
void WindowsConsole::enableANSISupport() const {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(out, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(out, mode);
}

#else

/**
 * \brief Set the console cursor visibility to the given flag.
 *
 * This function manipulates the console's cursor visibility using ANSI escape sequences.
 * It outputs the appropriate escape sequence to show or hide the cursor, as requested.
 *
 * \param[in] show_flag true to show the cursor, false to hide it.
 */
void UnixConsole::showCursor(bool show_flag) const {
    std::cout << (show_flag ? "\033[?25h" : "\033[?25l");
}

#endif

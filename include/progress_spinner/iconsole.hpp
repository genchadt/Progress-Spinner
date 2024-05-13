#ifndef ICONSOLE_HPP
#define ICONSOLE_HPP

#include <iostream>
#include <windows.h>

/**
 * \class IConsole
 * \brief Abstract base class for displaying progress indicators.
 * \details This class provides an abstract base class for console related functions.
 */
class IConsole {
    public:
        virtual ~IConsole() = default;
        virtual void clearLine() const = 0;
        virtual void showCursor(bool show_flag) const = 0;
};

/** 
 * \brief Implementation of IConsole for Windows
 * \details This class provides an implementation of IConsole for Windows.
 */
class WindowsConsole : public IConsole {
    public:
        /**
         * \brief Clear the current line
         * \details This function clears the current line in the console via ANSI escape codes.
         */
        void clearLine() const override {
            std::cout << "\r\033[K";
        }

        /**
         * \brief Show or hide the cursor
         * \details This function shows or hides the cursor in the console by using the Windows API.
         * \param show_flag
         */
        void showCursor(bool show_flag) const override {
            HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_CURSOR_INFO cursor_info;
            GetConsoleCursorInfo(out, &cursor_info);
            cursor_info.bVisible = show_flag;
            SetConsoleCursorInfo(out, &cursor_info);    
        }
};

/** 
 * \class UnixConsole
 * \brief Implementation of IConsole for Unix
 * \details This class provides an implementation of IConsole for Unix.
 */
class UnixConsole : public IConsole {
    public:
        /**
         * \brief Clear the current line
         * \details This function clears the current line in the console via ANSI escape codes.
         */
        void clearLine() const override {
            std::cout << "\r\033[K";
        }

        /**
         * \brief Show or hide the cursor
         * \details This function shows or hides the cursor in the console by using ANSI escape codes.
         * \param show_flag
         */
        void showCursor(bool show_flag) const override {
            std::cout << (show_flag ? "\033[?25h" : "\033[?25l");
        }
};

#ifdef _WIN32
using Console = WindowsConsole;
#else
using Console = UnixConsole;
#endif

#endif // ICONSOLE_HPP
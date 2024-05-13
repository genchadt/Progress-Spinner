#ifndef ICONSOLE_HPP
#define ICONSOLE_HPP

#include <iostream>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#endif

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

    protected:
        IConsole() {
            setUTF8();
        }

        /**
         * \brief Set the console codepage to UTF-8
         * \details This function sets the console codepage to UTF-8 by using the Windows API.
         */
        #ifdef _WIN32
        void setUTF8() const {
            try {
                UINT current_cp = GetConsoleOutputCP();
                if (current_cp != CP_UTF8) {
                    if (!SetConsoleOutputCP(CP_UTF8)) {
                        throw std::runtime_error("Failed to set console codepage to UTF-8");
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "Failed to set console codepage to UTF-8: " << e.what() << std::endl;
            }
        }
        #endif
};

/** 
 * \brief Implementation of IConsole for Windows
 * \details This class provides an implementation of IConsole for Windows.
 */
class WindowsConsole : public IConsole {
    public:
        WindowsConsole() = default;

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
        UnixConsole() = default;

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
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
        virtual void clearLine() const {
            std::cout << "\r\033[K";
        }
        virtual void showCursor(bool show_flag) const = 0;

    protected:
        IConsole() = default;
};

#ifdef _WIN32
/** 
 * \brief Implementation of IConsole for Windows
 * \details This class provides an implementation of IConsole for Windows.
 */
class WindowsConsole : public IConsole {
    public:
        WindowsConsole() {
            setUTF8();
            enableANSISupport();
        }

        void showCursor(bool show_flag) const override {
            HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_CURSOR_INFO cursor_info;
            GetConsoleCursorInfo(out, &cursor_info);
            cursor_info.bVisible = show_flag;
            SetConsoleCursorInfo(out, &cursor_info);
        }

    private:
        void setUTF8() const {
            SetConsoleOutputCP(CP_UTF8);
        }

        void enableANSISupport() const {
            HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
            DWORD mode = 0;
            GetConsoleMode(out, &mode);
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(out, mode);
        }
};

#else
/** 
 * \class UnixConsole
 * \brief Implementation of IConsole for Unix
 * \details This class provides an implementation of IConsole for Unix.
 */
class UnixConsole : public IConsole {
    public:
        UnixConsole() = default;

        void showCursor(bool show_flag) const override {
            std::cout << (show_flag ? "\033[?25h" : "\033[?25l");
        }
};
#endif

#ifdef _WIN32
using Console = WindowsConsole;
#else
using Console = UnixConsole;
#endif

#endif // ICONSOLE_HPP
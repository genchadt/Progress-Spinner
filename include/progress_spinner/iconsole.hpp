#ifndef ICONSOLE_HPP
#define ICONSOLE_HPP

#include <iostream>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

/**
 * \class IConsole
 * \brief Abstract base class for console related functions.
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
        /**
         * \brief Constructor for WindowsConsole
         * \details This constructor initializes a WindowsConsole by setting the console to
         *          output UTF-8 and enabling ANSI escape sequences.
         */
        WindowsConsole() {
            setUTF8();
            enableANSISupport();
        }

        /**
         * \brief Shows or hides the console cursor
         * \param[in] show_flag Flag indicating whether to show (true) or hide (false) the cursor
         */
        void showCursor(bool show_flag) const override {
            HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_CURSOR_INFO cursor_info;
            GetConsoleCursorInfo(out, &cursor_info);
            cursor_info.bVisible = show_flag;
            SetConsoleCursorInfo(out, &cursor_info);
        }

    private:
        /**
         * \brief Sets the console output code page to UTF-8
         * \details This function sets the console output code page to UTF-8, allowing the console to display
         *          Unicode characters correctly.
         */
        void setUTF8() const {
            SetConsoleOutputCP(CP_UTF8);
        }

        /**
         * \brief Enables ANSI escape sequence support for the console
         * \details This function enables ANSI escape sequence support for the console.
         */
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
 */
class UnixConsole : public IConsole {
    public:
        UnixConsole() = default;

        /**
         * \brief Shows or hides the console cursor
         * \param[in] show_flag Flag indicating whether to show (true) or hide (false) the cursor
         * \details This function shows or hides the console cursor. If the flag is true, the cursor is shown; otherwise, it is hidden.
         */
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
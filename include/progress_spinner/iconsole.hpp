#ifndef PROGRESS_INDICATOR_ICONSOLE_HPP
#define PROGRESS_INDICATOR_ICONSOLE_HPP

#include <iostream>

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
#include <windows.h>

class WindowsConsole : public IConsole {
public:
    WindowsConsole();
    void showCursor(bool show_flag) const override;

private:
    void setUTF8() const;
    void enableANSISupport() const;
};

#else

class UnixConsole : public IConsole {
public:
    UnixConsole() = default;
    void showCursor(bool show_flag) const override;
};

#endif

#ifdef _WIN32
using Console = WindowsConsole;
#else
using Console = UnixConsole;
#endif

#endif // PROGRESS_INDICATOR_ICONSOLE_HPP

// console.hpp
#ifndef CONSOLE_HPP
#define CONSOLE_HPP

/**
 * \class Console
 * \brief Handles console-specific operations like cursor visibility and line clearing.
 */
class Console {
public:
    void showCursor(bool show_flag);
    void clearLine();
};

#endif // CONSOLE_HPP

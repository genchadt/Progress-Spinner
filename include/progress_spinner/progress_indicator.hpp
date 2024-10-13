#ifndef PROGRESS_INDICATOR_PROGRESS_INDICATOR_HPP
#define PROGRESS_INDICATOR_PROGRESS_INDICATOR_HPP

#include <string>
#include <mutex>
#include "iconsole.hpp"

class ProgressIndicator {
public:
    ProgressIndicator(const std::string& progress_label = "Progress: ",
                      const std::string& completed_label = " ✓ OK!");
    virtual ~ProgressIndicator() = default;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void updateText(const std::string& new_text);

protected:
    std::string progress_label, completed_label;
    std::mutex mutex;
    Console console;

    void showCursor(bool show_flag);
    void clearLine();
};

#endif // PROGRESS_INDICATOR_PROGRESS_INDICATOR_HPP

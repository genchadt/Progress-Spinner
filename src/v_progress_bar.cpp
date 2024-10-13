#include "progress_spinner/v_progress_bar.hpp"
#include <cmath>
#include <iostream>
#include <mutex>
#include <stdexcept>

VProgressBar::VProgressBar(const VProgressBarOptions& options)
    : ProgressIndicator(options.progress_label, options.completed_label),
      chars(options.chars),
      completed(false),
      current_percentage(0.0),
      displayed_completed_label(false) {
    if (chars.empty()) {
        throw std::invalid_argument("char_frames cannot be empty.");
    }
    tick = 100.0 / (chars.size() - 1);
    showCursor(false);
    redraw();
}

void VProgressBar::start() {}

void VProgressBar::stop() {
    clearLine();
    std::cout << progress_label << completed_label << std::endl;
    std::cout << std::flush;
    showCursor(true);
}

void VProgressBar::updateProgress(double new_percentage) {
    std::lock_guard<std::mutex> lock(mutex);

    if (new_percentage >= 100.0) {
        new_percentage = 100.0;
        if (!completed) {
            completed = true;
            stop();
            return;
        }
    } else {
        completed = false;
    }

    current_percentage = new_percentage;
    redraw();
}

void VProgressBar::updateText(const std::string& new_text) {
    std::lock_guard<std::mutex> lock(mutex);
    progress_label = new_text;
    completed = false;
    displayed_completed_label = false;
    redraw();
}

void VProgressBar::redraw() {
    clearLine();
    std::cout << progress_label;

    double percentage = std::min(current_percentage, 100.0);
    size_t index = static_cast<size_t>(std::round((percentage / 100.0) * (chars.size() - 1)));
    index = std::min(index, chars.size() - 1);

    std::cout << chars[index] << std::flush;
}

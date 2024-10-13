#include "progress_spinner/h_progress_bar.hpp"
#include <cmath>
#include <iostream>
#include <mutex>
#include <stdexcept>


HProgressBar::HProgressBar(const HProgressBarOptions& options)
    : ProgressIndicator(options.progress_label, options.completed_label),
      total_segments(options.total_segments),
      chars(options.chars),
      current_segments(0) {
    if (total_segments <= 0) {
        throw std::invalid_argument("Total segments must be greater than 0.");
    }
    if (chars.size() < 2) {
        throw std::invalid_argument("At least two characters are required for HProgressBar (empty and filled).");
    }
    showCursor(false);
}

void HProgressBar::start() {
    updateProgress(0);
}

void HProgressBar::stop() {
    std::lock_guard<std::mutex> lock(mutex);
    current_segments = total_segments;
    redraw(true);
    clearLine();
    std::cout << progress_label << completed_label << std::endl;
    showCursor(true);
}

void HProgressBar::updateProgress(double new_percentage) {
    std::lock_guard<std::mutex> lock(mutex);
    current_segments = static_cast<int>(std::round(new_percentage / 100 * total_segments));
    redraw(false);
}

void HProgressBar::redraw(bool is_final) {
    clearLine();
    std::cout << progress_label;
    for (int i = 0; i < current_segments; ++i) {
        std::cout << chars[1];
    }
    for (int i = current_segments; i < total_segments; ++i) {
        std::cout << chars[0];
    }
    if (!is_final) {
        std::cout << std::flush;
    }
}

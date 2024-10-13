#include "progress_spinner/h_progress_bar.hpp"
#include <cmath>
#include <iostream>
#include <mutex>
#include <stdexcept>

HProgressBar::HProgressBar(const HProgressBarOptions& options)
    : ProgressIndicator(options.progress_label, options.completed_label),
      total_segments(options.total_segments),
      chars(options.chars),
      current_segments(0),
      use_brackets(options.use_brackets) {
    if (total_segments <= 0) {
        throw std::invalid_argument("Total segments must be greater than 0.");
    }

    size_t expected_size = use_brackets ? 4 : 2;
    if (chars.size() != expected_size) {
        throw std::invalid_argument("Incorrect number of characters provided for HProgressBar.");
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
    if (new_percentage < 0) new_percentage = 0;
    if (new_percentage > 100) new_percentage = 100;

    current_segments = static_cast<int>(std::round(new_percentage / 100 * total_segments));
    redraw(false);
}

void HProgressBar::updateText(const std::string& new_text) {
    std::lock_guard<std::mutex> lock(mutex);
    progress_label = new_text;
    redraw(false);
}

void HProgressBar::redraw(bool is_final) {
    clearLine();
    std::cout << progress_label;

    size_t empty_char_index = use_brackets ? 2 : 0;
    size_t filled_char_index = use_brackets ? 3 : 1;

    // Start bracket
    if (use_brackets) {
        std::cout << chars[0];
    }

    // Progress bar
    for (int i = 0; i < current_segments; ++i) {
        std::cout << chars[filled_char_index];
    }
    for (int i = current_segments; i < total_segments; ++i) {
        std::cout << chars[empty_char_index];
    }

    // End bracket
    if (use_brackets) {
        std::cout << chars[1];
    }

    if (!is_final) {
        std::cout << std::flush;
    }
}

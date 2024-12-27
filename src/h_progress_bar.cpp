#include "progress_spinner/h_progress_bar.hpp"
#include <cmath>
#include <iostream>
#include <mutex>

HProgressBar::HProgressBar(const HProgressBarOptions& options)
    : ProgressIndicator(options.progress_label, options.completed_label),
      total_segments(options.total_segments),
      progress_chars(options.progress_chars),
      bracket_chars(options.bracket_chars),
      current_segments(0),
      options(&options) {
    if (total_segments <= 0) {
        throw std::invalid_argument("Total segments must be greater than 0.");
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

    char empty_char = progress_chars[0][0];
    char filled_char = progress_chars[1][0];

    // Start bracket
    if (options->has_brackets()) {
        std::cout << bracket_chars[0];
    }

    // Progress bar
    for (int i = 0; i < current_segments; ++i) {
        std::cout << filled_char;
    }
    for (int i = current_segments; i < total_segments; ++i) {
        std::cout << empty_char;
    }

    // End bracket
    if (options->has_brackets()) {
        std::cout << bracket_chars[1];
    }

    if (!is_final) {
        std::cout << std::flush;
    }
}

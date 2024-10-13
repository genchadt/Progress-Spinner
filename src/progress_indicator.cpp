#include "progress_spinner/progress_indicator.hpp"

ProgressIndicator::ProgressIndicator(const std::string& progress_label,
                                     const std::string& completed_label)
    : progress_label(progress_label),
      completed_label(completed_label),
      console() {}

void ProgressIndicator::updateText(const std::string& new_text) {
    std::lock_guard<std::mutex> lock(mutex);
    progress_label = new_text;
}

void ProgressIndicator::showCursor(bool show_flag) {
    console.showCursor(show_flag);
}

void ProgressIndicator::clearLine() {
    console.clearLine();
}

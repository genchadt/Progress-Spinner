#include "progress_spinner/progress_spinner.hpp"
#include <cmath>
#include <iostream>
#include <mutex>
#include <stdexcept>

ProgressSpinner::ProgressSpinner(const ProgressSpinnerOptions& options)
    : ProgressIndicator(options.progress_label, options.completed_label),
      chars(options.chars),
      keep_alive(true),
      update_interval_ms(options.update_interval_ms),
      stopped(false) {
    if (chars.empty()) {
        throw std::invalid_argument("Char frames vector may not be empty.");
    }
}

ProgressSpinner::~ProgressSpinner() {
    stop();
}

void ProgressSpinner::start() {
    showCursor(false);
    spinner_thread = std::thread(&ProgressSpinner::run, this);
}

void ProgressSpinner::stop() {
    {
        std::lock_guard<std::mutex> lock(mutex);
        if (stopped) {
            return;
        }
        stopped = true;
        keep_alive = false;
    }
    if (spinner_thread.joinable()) {
        spinner_thread.join();
    }
    {
        std::lock_guard<std::mutex> lock(mutex);
        clearLine();
        std::cout << "\r" << progress_label << completed_label << std::endl;
        showCursor(true);
    }
}

void ProgressSpinner::run() {
    size_t index = 0;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(update_interval_ms));
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (!keep_alive) {
                break;
            }
            std::cout << "\r" << progress_label << chars[index] << std::flush;
        }
        index = (index + 1) % chars.size();
    }
}

#include "progress_spinner/progress_spinner.hpp"
#include <iostream>
#include <mutex>

/**
 * \brief Construct a ProgressSpinner.
 *
 * \param options A ProgressSpinnerOptions object.
 *
 * Creates a ProgressSpinner object and starts a separate thread to update the
 * spinner animation. The spinner animation is updated every update_interval_ms
 * milliseconds.
 *
 * \throws std::invalid_argument if the char_frames vector in options is
 * empty.
 */
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

/**
 * \brief Destructor for ProgressSpinner.
 *
 * Calls stop() to ensure that the spinner thread is joined before the object
 * is destroyed.
 */
ProgressSpinner::~ProgressSpinner() {
    stop();
}

/**
 * \brief Starts the spinner animation in a separate thread.
 *
 * Calls showCursor(false) to hide the cursor and starts a separate thread to
 * update the spinner animation. The animation is updated every
 * update_interval_ms milliseconds.
 */
void ProgressSpinner::start() {
    showCursor(false);
    spinner_thread = std::thread(&ProgressSpinner::run, this);
}

/**
 * \brief Stops the spinner animation.
 *
 * Joins the spinner thread and updates the display to show the completed
 * label. Also shows the cursor again.
 */
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

/**
 * \brief Function to be run in a separate thread to update the spinner animation.
 *
 * The function runs an infinite loop, which is broken when the keep_alive
 * variable is set to false. The loop sleeps for update_interval_ms
 * milliseconds, then updates the display to show the next frame in the
 * spinner animation.
 */
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

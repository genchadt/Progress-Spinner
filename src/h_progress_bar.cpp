#include "progress_spinner/h_progress_bar.hpp"
#include <cmath>
#include <iostream>
#include <mutex>
#include <stdexcept>


/**
 * \brief Constructor for HProgressBar
 *
 * \param options HProgressBarOptions which contains the configuration for HProgressBar
 *
 * HProgressBar constructor validates the options and throws std::invalid_argument if
 * total_segments is less than or equal to 0 or if the number of characters in chars is less than 2.
 * It also sets the cursor to false.
 */
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

/**
 * \brief Start the progress bar by updating the progress to 0.
 *
 * This is a convenience method to start the progress bar at 0%.
 */
void HProgressBar::start() {
    updateProgress(0);
}

/**
 * \brief Stop the progress bar
 *
 * Stopping the progress bar updates the progress to 100%, redraws the bar
 * with the completed label, and shows the cursor.
 */
void HProgressBar::stop() {
    std::lock_guard<std::mutex> lock(mutex);
    current_segments = total_segments;
    redraw(true);
    clearLine();
    std::cout << progress_label << completed_label << std::endl;
    showCursor(true);
}

/**
 * \brief Update the progress bar by updating the progress to new_percentage.
 *
 * This method does not need to be thread-safe as it is already protected by a mutex.
 * \param new_percentage New percentage value between 0 and 100.
 * \note If new_percentage is less than 0, the progress bar remains at 0.
 *       If new_percentage is greater than 100, the progress bar remains at 100.
 */
void HProgressBar::updateProgress(double new_percentage) {
    std::lock_guard<std::mutex> lock(mutex);
    current_segments = static_cast<int>(std::round(new_percentage / 100 * total_segments));
    redraw(false);
}

/**
 * \brief Redraw the progress bar with the current progress
 *
 * This function redraws the progress bar based on the current progress. If
 * is_final is true, then the final label is displayed and the cursor is shown.
 * Otherwise, the progress bar is redrawn and the cursor remains hidden.
 * \param is_final Whether the final label should be displayed
 */
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

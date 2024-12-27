#include "progress_spinner/v_progress_bar.hpp"
#include <cmath>
#include <iostream>
#include <mutex>

/**
 * \brief Constructor for VProgressBar.
 *
 * \param options VProgressBarOptions which contains the configuration for VProgressBar
 *
 * VProgressBar constructor validates the options and throws std::invalid_argument if
 * char_frames is empty. It also sets the cursor to false and calls `redraw()` to
 * display the initial bar.
 */
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

/**
 * \brief Start the progress bar.
 *
 * This function is not implemented for VProgressBar since it does not have a
 * concept of starting or stopping. It is only included for API consistency with
 * HProgressBar and ProgressSpinner.
 */
void VProgressBar::start() {}

/**
 * \brief Stop the progress bar.
 *
 * Stop the progress bar, redraw the bar with the completed label, and show the
 * cursor. This is usually called when the task is complete.
 */
void VProgressBar::stop() {
    clearLine();
    std::cout << progress_label << completed_label << std::endl;
    std::cout << std::flush;
    showCursor(true);
}

/**
 * \brief Update the progress bar by updating the progress to new_percentage.
 *
 * This method does not need to be thread-safe as it is already protected by a mutex.
 * If new_percentage is 100 or greater, the progress bar will be stopped and the
 * completed label will be displayed. Otherwise, the progress bar will be redrawn
 * with the updated progress.
 * \param new_percentage New percentage value between 0 and 100.
 * \note If new_percentage is less than 0, the progress bar remains at 0.
 *       If new_percentage is greater than 100, the progress bar remains at 100.
 */
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

/**
 * \brief Update the label displayed by the vertical progress bar.
 *
 * \param new_text The new label string.
 *
 * This method does not need to be thread-safe as it is already protected by a mutex.
 * The label is updated and the bar is redrawn with the new label.
 */
void VProgressBar::updateText(const std::string& new_text) {
    std::lock_guard<std::mutex> lock(mutex);
    progress_label = new_text;
    completed = false;
    displayed_completed_label = false;
    redraw();
}


/**
 * \brief Redraw the vertical progress bar with the updated progress.
 *
 * This method redoes the vertical progress bar, using the current percentage
 * value to determine which frame to display. The frame index is calculated as
 * `(percentage / final_frame_threshold) * (num_frames - frame_offset)`.
 * The final frame is shown if the percentage is greater than or equal to
 * `final_frame_threshold`. The frame index is clamped to the valid range
 * `[frame_offset, num_frames - frame_offset)`.
 *
 * \note This method is thread-safe as it is protected by a mutex.
 */
void VProgressBar::redraw() {
    using std::min;  // Ensure std::min is used to avoid macro conflicts

    const double final_frame_threshold = 75.0;  // Threshold to start showing the final frame
    const size_t frame_offset = 1;              // Offset to map percentage to frame index

    double percentage = min(current_percentage, 100.0);
    double scaled_percentage = (percentage / final_frame_threshold);
    size_t num_frames = chars.size();
    size_t frame_index = static_cast<size_t>(
        std::floor(scaled_percentage * (num_frames - frame_offset))
    );

    frame_index = min(frame_index, num_frames - frame_offset);

    clearLine();
    std::cout << progress_label << chars[frame_index] << std::flush;
}

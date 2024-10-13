#include "progress_spinner/progress_indicator.hpp"

/**
 * \brief Constructor for ProgressIndicator.
 *
 * \param progress_label The initial label string.
 * \param completed_label The string to display when the task is complete.
 */
ProgressIndicator::ProgressIndicator(const std::string& progress_label,
                                     const std::string& completed_label)
    : progress_label(progress_label),
      completed_label(completed_label),
      console() {}

/**
 * \brief Updates the label displayed by the progress indicator.
 *
 * \param new_text The new label string.
 */
void ProgressIndicator::updateText(const std::string& new_text) {
    std::lock_guard<std::mutex> lock(mutex);
    progress_label = new_text;
}

/**
 * \brief Controls the visibility of the cursor.
 *
 * \param show_flag true to show the cursor, false to hide it.
 */
void ProgressIndicator::showCursor(bool show_flag) {
    console.showCursor(show_flag);
}

/**
 * \brief Clears the current line of the console.
 *
 * This function outputs the necessary escape sequence to clear the current line
 * of the console, so that the next output will overwrite the current line.
 */
void ProgressIndicator::clearLine() {
    console.clearLine();
}

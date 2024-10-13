#include "progress_spinner/options.hpp"

/**
 * \brief Constructor for ProgressSpinnerOptions.
 *
 * \param label The initial label string.
 * \param completed_label The string to display when the task is complete.
 * \param char_frames A sequence of characters used to represent the spinner.
 * \param update_interval_ms The interval in milliseconds between each frame update.
 */
ProgressSpinnerOptions::ProgressSpinnerOptions(const option::Label& label,
                                               const option::CompletedLabel& completed_label,
                                               const option::CharFrames& char_frames,
                                               const option::UpdateIntervalMs& update_interval_ms)
    : progress_label(label.progress_label),
      completed_label(completed_label.completed_label),
      chars(char_frames),
      update_interval_ms(update_interval_ms.update_interval_ms) {}

/**
 * \brief Constructor for HProgressBarOptions.
 *
 * \param label The initial label string.
 * \param completed_label The string to display when the task is complete.
 * \param segments The total number of segments in the bar.
 * \param char_frames A sequence of characters used to represent filled segments.
 *                    The first character is used for empty segments, and the last
 *                    character is used for filled segments. If the sequence is
 *                    less than 2 characters, the default of "░" and "█" is used.
 */
#include "progress_spinner/options.hpp"
#include <stdexcept>

HProgressBarOptions::HProgressBarOptions(const option::Label& label,
                                         const option::CompletedLabel& completed_label,
                                         const option::NumOfSegments& segments,
                                         const option::CharFrames& char_frames,
                                         bool use_brackets)
    : progress_label(label.progress_label),
      completed_label(completed_label.completed_label),
      total_segments(segments.number_of_segments),
      chars(char_frames),
      use_brackets(use_brackets) {
    // If brackets are to be used
    if (use_brackets) {
        if (chars.size() == 2) {
            // Automatically add default brackets if only two characters are provided
            chars.insert(chars.begin(), {std::string("["), std::string("]")});  // Corrected
        } else if (chars.size() != 4) {
            throw std::invalid_argument("When use_brackets is true, char_frames must have either 2 or 4 characters.");
        }
    } else if (chars.size() != 2) {
        // Without brackets, we expect exactly 2 characters
        throw std::invalid_argument("When use_brackets is false, char_frames must have exactly 2 characters.");
    }
}

/**
 * \brief Constructor for VProgressBarOptions.
 *
 * \param label The initial label string.
 * \param completed_label The string to display when the task is complete.
 * \param char_frames A sequence of characters used to represent the vertical
 *                    progress bar. The first character is used for empty
 *                    segments, and subsequent characters are used for filled
 *                    segments. If the sequence is empty, the default of " ",
 *                    "▁", "▂", "▃", "▄", "▅", "▆", "▇", and "█" is used.
 */
VProgressBarOptions::VProgressBarOptions(const option::Label& label,
                                         const option::CompletedLabel& completed_label,
                                         const option::CharFrames& char_frames)
    : progress_label(label.progress_label),
      completed_label(completed_label.completed_label),
      chars(char_frames) {}

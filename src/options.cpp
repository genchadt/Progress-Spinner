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

HProgressBarOptions::HProgressBarOptions(const option::Label& label,
                                         const option::CompletedLabel& completed_label,
                                         const option::NumOfSegments& segments,
                                         const option::CharFrames& char_frames)
    : progress_label(label.progress_label),
      completed_label(completed_label.completed_label),
      total_segments(segments.number_of_segments),
      chars(char_frames) {
    if (chars.size() < 2) {
        chars = option::CharFrames({"░", "█"});
    }
}

VProgressBarOptions::VProgressBarOptions(const option::Label& label,
                                         const option::CompletedLabel& completed_label,
                                         const option::CharFrames& char_frames)
    : progress_label(label.progress_label),
      completed_label(completed_label.completed_label),
      chars(char_frames) {}

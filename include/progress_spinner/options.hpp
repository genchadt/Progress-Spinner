#ifndef PROGRESS_INDICATOR_OPTIONS_HPP
#define PROGRESS_INDICATOR_OPTIONS_HPP

#include <initializer_list>
#include <stdexcept>
#include <string>
#include <vector>

namespace option {

struct CompletedLabel {
    std::string completed_label = " ✓ OK!";
};

struct Label {
    std::string progress_label = "Progress: ";
};

struct NumOfSegments {
    int number_of_segments = 30;
};

struct CharFrames : public std::vector<std::string> {
/**
 * \brief Constructor for CharFrames.
 *
 * \param char_list The sequence of characters used to represent the progress
 *                  bar. The first character is used for empty segments, and the
 *                  last character is used for filled segments. If the sequence
 *                  is less than 2 characters, the default of " " and "█" is
 *                  used.
 */
    CharFrames(const std::initializer_list<std::string>& char_list)
        : std::vector<std::string>(char_list) {}
};

struct UpdateIntervalMs {
    int update_interval_ms = 100;
};

} // namespace option

struct ProgressSpinnerOptions {
    std::string progress_label;
    std::string completed_label;
    option::CharFrames chars;
    int update_interval_ms;

    ProgressSpinnerOptions(const option::Label& label = option::Label(),
                           const option::CompletedLabel& completed_label = option::CompletedLabel(),
                           const option::CharFrames& char_frames = option::CharFrames({"|", "/", "-", "\\"}),
                           const option::UpdateIntervalMs& update_interval_ms = option::UpdateIntervalMs());
};

struct HProgressBarOptions {
    std::string progress_label;
    std::string completed_label;
    int total_segments;
    option::CharFrames chars;
    bool use_brackets;

    HProgressBarOptions(const option::Label& label = option::Label(),
                        const option::CompletedLabel& completed_label = option::CompletedLabel(),
                        const option::NumOfSegments& segments = option::NumOfSegments{30},
                        const option::CharFrames& char_frames = option::CharFrames({"[", "]", "░", "█"}),
                        bool use_brackets = true);
};


struct VProgressBarOptions {
    std::string progress_label;
    std::string completed_label;
    option::CharFrames chars;

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
    VProgressBarOptions(const option::Label& label = option::Label(),
                        const option::CompletedLabel& completed_label = option::CompletedLabel(),
                        const option::CharFrames& char_frames = option::CharFrames({" ", "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"}));
};

#endif // PROGRESS_INDICATOR_OPTIONS_HPP

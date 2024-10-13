#ifndef PROGRESS_INDICATOR_OPTIONS_HPP
#define PROGRESS_INDICATOR_OPTIONS_HPP

#include <string>
#include <vector>
#include <initializer_list>

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

    // Declaration only (no inline definition)
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

    // Declaration only (no inline definition)
    HProgressBarOptions(const option::Label& label = option::Label(),
                        const option::CompletedLabel& completed_label = option::CompletedLabel(),
                        const option::NumOfSegments& segments = option::NumOfSegments{30},
                        const option::CharFrames& char_frames = option::CharFrames({"░", "█"}));
};

struct VProgressBarOptions {
    std::string progress_label;
    std::string completed_label;
    option::CharFrames chars;

    // Declaration only (no inline definition)
    VProgressBarOptions(const option::Label& label = option::Label(),
                        const option::CompletedLabel& completed_label = option::CompletedLabel(),
                        const option::CharFrames& char_frames = option::CharFrames({" ", "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"}));
};

#endif // PROGRESS_INDICATOR_OPTIONS_HPP

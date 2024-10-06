#include <string>
#include <vector>

namespace option {
    struct CompletedLabel
    {
        std::string completed_label = " ✓ OK!";
    };

    struct Label
    {
        std::string progress_label = "Progress: ";
    };

    struct NumOfSegments
    {
        int number_of_segments = 30;
    };

    struct ProgressBarChars
    {
        std::vector<std::string> progress_bar_chars = {"░", "█"};
    };

    struct SpinnerChars
    {
        std::vector<std::string> spinner_chars = {"|", "/", "-", "\\"};
    };

    struct UpdateIntervalMs
    {
        int update_interval_ms = 100;
    };
}

struct ProgressSpinnerOptions 
{
    std::string progress_label;
    std::string completed_label;
    std::vector<std::string> char_frames;
    int update_interval_ms;

    ProgressSpinnerOptions(const option::Label& label = option::Label(),
                           const option::CompletedLabel& completed_label = option::CompletedLabel(),
                           const option::SpinnerChars& char_frames = option::SpinnerChars(),
                           const option::UpdateIntervalMs& update_interval_ms = option::UpdateIntervalMs())
        : progress_label(label.progress_label),
          completed_label(completed_label.completed_label),
          char_frames(char_frames.spinner_chars),
          update_interval_ms(update_interval_ms.update_interval_ms) {}
};

struct HProgressBarOptions {
    std::string progress_label;
    std::string completed_label;
    int total_segments;
    std::string empty_char;
    std::string filled_char;

    HProgressBarOptions(const option::Label& label = option::Label(),
                        const option::CompletedLabel& completed_label = option::CompletedLabel(),
                        const option::NumOfSegments& segments = option::NumOfSegments{30},
                        const option::ProgressBarChars& chars = option::ProgressBarChars())
        : progress_label(label.progress_label),
          completed_label(completed_label.completed_label),
          total_segments(segments.number_of_segments),
          empty_char(chars.progress_bar_chars.size() > 0 ? chars.progress_bar_chars[0] : "░"),
          filled_char(chars.progress_bar_chars.size() > 1 ? chars.progress_bar_chars[1] : "█") {}
};


struct VProgressBarOptions
{
    std::string progress_label;
    std::string completed_label;
    std::vector<std::string> char_frames;

    VProgressBarOptions(const option::Label& label = option::Label(),
                        const option::CompletedLabel& completed_label = option::CompletedLabel(),
                        const option::ProgressBarChars& char_frames = option::ProgressBarChars())
        : progress_label(label.progress_label),
          completed_label(completed_label.completed_label),
          char_frames(char_frames.progress_bar_chars) {}
};
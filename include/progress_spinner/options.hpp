#include <initializer_list>
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

    struct CharFrames : public std::vector<std::string> {
        CharFrames(const std::initializer_list<std::string>& char_list)
            : std::vector<std::string>(char_list) {}
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
    option::CharFrames chars;
    int update_interval_ms;

    /**
     * \brief Constructor for ProgressSpinnerOptions
     * \details Sets the options for ProgressSpinner to the given values.
     * \param[in] label Initial text displayed as the progress label. Can be changed during runtime.
     * \param[in] completed_label Text displayed upon completion.
     * \param[in] char_frames Vector of characters to use for the progress spinner.
     * \param[in] update_interval_ms Interval between frame updates in milliseconds.
     */
    ProgressSpinnerOptions(const option::Label& label = option::Label(),
                           const option::CompletedLabel& completed_label = option::CompletedLabel(),
                           const option::CharFrames& char_frames = option::CharFrames({"|", "/", "-", "\\"}),
                           const option::UpdateIntervalMs& update_interval_ms = option::UpdateIntervalMs())
        : progress_label(label.progress_label),
          completed_label(completed_label.completed_label),
          chars(char_frames),
          update_interval_ms(update_interval_ms.update_interval_ms) {}
};

struct HProgressBarOptions {
    std::string progress_label;
    std::string completed_label;
    int total_segments;
    option::CharFrames chars;

    /**
     * \brief Constructor for HProgressBarOptions
     * \details Sets the options for HProgressBar to the given values.
     * \param[in] label Initial text displayed as the progress label.
     * \param[in] completed_label Text displayed upon completion.
     * \param[in] segments Total number of segments in the progress bar.
     * \param[in] char_frames Vector of characters to use for the progress bar.
     */
    HProgressBarOptions(const option::Label& label = option::Label(),
                        const option::CompletedLabel& completed_label = option::CompletedLabel(),
                        const option::NumOfSegments& segments = option::NumOfSegments{30},
                        const option::CharFrames& char_frames = option::CharFrames({"░", "█"}))
        : progress_label(label.progress_label),
          completed_label(completed_label.completed_label),
          total_segments(segments.number_of_segments),
          chars(char_frames) {
        if (chars.size() < 2) {
            chars = option::CharFrames({"░", "█"});
        }
    }
};


struct VProgressBarOptions
{
    std::string progress_label;
    std::string completed_label;
    option::CharFrames chars;

    /**
     * \brief Constructor for VProgressBarOptions
     * \details Sets the options for VProgressBar to the given values.
     * \param[in] label Initial text displayed as the progress label.
     * \param[in] completed_label Text displayed upon completion.
     * \param[in] char_frames Vector of characters to use for the progress bar.
     */
    VProgressBarOptions(const option::Label& label = option::Label(),
                        const option::CompletedLabel& completed_label = option::CompletedLabel(),
                        const option::CharFrames& char_frames = option::CharFrames({" ", "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"}))
        : progress_label(label.progress_label),
          completed_label(completed_label.completed_label),
          chars(char_frames) {}
};
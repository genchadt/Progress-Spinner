#ifndef PROGRESS_INDICATOR_H_PROGRESS_BAR_HPP
#define PROGRESS_INDICATOR_H_PROGRESS_BAR_HPP

#include "progress_indicator.hpp"
#include "options.hpp"

class HProgressBar : public ProgressIndicator {
public:
    HProgressBar(const HProgressBarOptions& options = HProgressBarOptions());

    void start() override;
    void stop() override;
    void updateProgress(double new_percentage);
    void updateText(const std::string& new_text) override;

private:
    int total_segments;
    int current_segments;
    option::CharFrames progress_chars;
    option::CharFrames bracket_chars;
    // const HProgressBarOptions* options;
    bool use_brackets_flag_;

    void redraw(bool is_final = false);
};

#endif // PROGRESS_INDICATOR_H_PROGRESS_BAR_HPP

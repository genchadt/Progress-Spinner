#ifndef PROGRESS_INDICATOR_H_PROGRESS_BAR_HPP
#define PROGRESS_INDICATOR_H_PROGRESS_BAR_HPP

#include "progress_indicator.hpp"
#include "options.hpp"
#include <stdexcept>

class HProgressBar : public ProgressIndicator {
public:
    HProgressBar(const HProgressBarOptions& options = HProgressBarOptions());

    void start() override;
    void stop() override;
    void updateProgress(double new_percentage);

private:
    int total_segments;
    int current_segments;
    option::CharFrames chars;

    void redraw(bool is_final = false);
};

#endif // PROGRESS_INDICATOR_H_PROGRESS_BAR_HPP

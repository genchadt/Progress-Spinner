#ifndef PROGRESS_INDICATOR_V_PROGRESS_BAR_HPP
#define PROGRESS_INDICATOR_V_PROGRESS_BAR_HPP

#include "progress_indicator.hpp"
#include "options.hpp"

class VProgressBar : public ProgressIndicator {
public:
    VProgressBar(const VProgressBarOptions& options = VProgressBarOptions());

    void start() override;
    void stop() override;
    void updateProgress(double new_percentage);
    void updateText(const std::string& new_text) override;

    double getTick() const {
        return tick;
    }

private:
    option::CharFrames chars;
    double current_percentage;
    double tick;
    bool completed;
    bool displayed_completed_label;

    void redraw();
};

#endif // PROGRESS_INDICATOR_V_PROGRESS_BAR_HPP

#ifndef PROGRESS_INDICATOR_PROGRESS_SPINNER_HPP
#define PROGRESS_INDICATOR_PROGRESS_SPINNER_HPP

#include "progress_indicator.hpp"
#include "options.hpp"
#include <atomic>
#include <thread>

class ProgressSpinner : public ProgressIndicator {
public:
    ProgressSpinner(const ProgressSpinnerOptions& options = ProgressSpinnerOptions());
    ~ProgressSpinner();

    void start() override;
    void stop() override;

private:
    option::CharFrames chars;
    std::atomic<bool> keep_alive;
    std::thread spinner_thread;
    int update_interval_ms;
    bool stopped;

    void run();
};

#endif // PROGRESS_INDICATOR_PROGRESS_SPINNER_HPP

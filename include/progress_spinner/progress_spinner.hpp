//      ____                                          _____       _                      
//     / __ \_________  ____ _________  __________   / ___/____  (_)___  ____  ___  _____
//    / /_/ / ___/ __ \/ __ `/ ___/ _ \/ ___/ ___/   \__ \/ __ \/ / __ \/ __ \/ _ \/ ___/
//   / ____/ /  / /_/ / /_/ / /  /  __(__  |__  )   ___/ / /_/ / / / / / / / /  __/ /    
//  /_/   /_/   \____/\__, /_/   \___/____/____/   /____/ .___/_/_/ /_/_/ /_/\___/_/     
//                   /____/                            /_/                               
/**
 * \file progress_spinner.hpp
 * \brief Abstract base class for displaying progress indicators.
 * \details This class provides an abstract base class for displaying a variety of progress indicators.
 */
#ifndef PROGRESS_INDICATOR_HPP
#define PROGRESS_INDICATOR_HPP

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>
#include "iconsole.hpp"
#include "options.hpp"

/**
 * \class ProgressIndicator
 * \brief Abstract base class for displaying progress indicators.
 */
class ProgressIndicator {
public:
    /**
     * \brief Constructor for ProgressIndicator.
     * \param[in] progress_label Initial text displayed as the progress label.
     * \param[in] completed_label Text displayed upon completion.
     */
    ProgressIndicator(  const std::string& progress_label = "Progress: ",
                        const std::string& completed_label = " ✓ OK!"  )
    :   progress_label(progress_label),
        completed_label(completed_label),
        console() {}

    virtual ~ProgressIndicator() = default;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void updateText(const std::string& new_text) {
        std::lock_guard<std::mutex> lock(mutex);
        progress_label = new_text;
    }

protected:
    std::string progress_label, completed_label;
    std::mutex mutex;
    Console console;

    void showCursor(bool show_flag) {
        console.showCursor(show_flag);
    }

    void clearLine() {
        console.clearLine();
    }
};

/**
 * \class VProgressBar
 * \brief Class for displaying a progress bar.
 * \details This class provides a visual representation of progress through a single-character vertically-filling bar.
 * \see https://en.wikipedia.org/wiki/Block_Elements
 */
class VProgressBar : public ProgressIndicator {
public:
    /** 
     * \brief Constructor for VProgressBar
     * \param[in] progress_label Initial text displayed as the progress label.
     * \param[in] completed_label Text displayed upon completion.
     * \param[in] char_frames Vector of characters to use for the progress bar.
     * \throws std::invalid_argument if char_frames is empty.
    */
    VProgressBar(const VProgressBarOptions& options = VProgressBarOptions())
        : ProgressIndicator(options.progress_label, options.completed_label),
          chars(options.chars),
          completed(false),
          current_percentage(0.0) {
            if (chars.empty()) {
                throw std::invalid_argument("char_frames cannot be empty.");
            }
            tick = 100.0 / (chars.size() - 1);
            showCursor(false);
            redraw();
          }

    void start() override {}

    /**
     * \brief Stops the progress bar
     * \details Clears the progress bar and displays the completed message.
     */
    void stop() override {
        clearLine();
        std::cout << progress_label << completed_label << std::endl;
        std::cout << std::flush;
        showCursor(true);
    }

    /**
     * \brief Updates the progress bar
     * \details Redraws the progress bar with the new percentage value.
     * \param new_percentage 
     */
    void updateProgress(double new_percentage) {
        std::lock_guard<std::mutex> lock(mutex);

        if (new_percentage >= 100.0) {
            new_percentage = 100.0;
            if (!completed) {
                completed = true;
                // Automatically stop when progress reaches 100%
                stop();  // Stop includes the final redraw with completion message
                return;  // Exit function to avoid further drawing
            }
        } else {
            completed = false;
        }

        current_percentage = new_percentage;
        redraw();
    }

    void updateText(const std::string& new_text) override {
        std::lock_guard<std::mutex> lock(mutex);
        progress_label = new_text;
        // Reset state variables
        completed = false;
        displayed_completed_label = false;
        redraw();
    }

    double getCurrentPercentage() const { return current_percentage; }
    size_t getCharCount() const { return chars.size(); }
    double getTick() const { return tick; }

private:
    option::CharFrames chars;
    double current_percentage;
    double tick;
    bool completed;
    bool displayed_completed_label;

    void redraw() {
        clearLine();
        std::cout << progress_label;

        // Ensure percentage doesn't exceed 100%
        double percentage = std::min(current_percentage, 100.0);

        // Calculate index with proper rounding
        size_t index = static_cast<size_t>(std::round((percentage / 100.0) * (chars.size() - 1)));

        // Ensure index doesn't exceed chars.size() - 1
        index = std::min(index, chars.size() - 1);

        std::cout << chars[index] << std::flush;
    }
};

/**
 * \class HProgressBar
 * \brief Class for displaying a horizontal progress bar using block characters.
 * \details This class visually represents progress through a customizable horizontal bar made up of block characters.
 * \see https://en.wikipedia.org/wiki/Block_Elements
 */
class HProgressBar : public ProgressIndicator {
public:
    /**
     * \brief Constructor for HProgressBar
     * \param[in] progress_label Initial text displayed as the progress label.
     * \param[in] completed_label Text displayed upon completion.
     * \param[in] total_segments Total number of segments in the progress bar.
     * \param[in] empty_char Character to use for empty segments.
     * \param[in] filled_char Character to use for filled segments.
     * \see https://en.wikipedia.org/wiki/Block_Elements
     */
    HProgressBar(const HProgressBarOptions& options = HProgressBarOptions())
        : ProgressIndicator(options.progress_label, options.completed_label),
          total_segments(options.total_segments),
          chars(options.chars),
          current_segments(0) {
        if (total_segments <= 0) {
            throw std::invalid_argument("Total segments must be greater than 0.");
        }
        if (chars.size() < 2) {
            throw std::invalid_argument("At least two characters are required for HProgressBar (empty and filled).");
        }
        showCursor(false);
    }

    /**
     * \brief Starts the progress bar
     * \details Initializes the progress bar and sets the current segments to 0.
     */
    void start() override {
        updateProgress(0); // Initialize progress bar
    }

    /**
     * \brief Stops the progress bar
     * \details Clears the progress bar and displays the completed message.
     */
    void stop() override {
        std::lock_guard<std::mutex> lock(mutex);
        current_segments = total_segments; // Ensure bar is full
        redraw(true); // Redraw one last time with full progress
        clearLine();
        std::cout << progress_label << completed_label << std::endl;
        showCursor(true);
    }

    /**
     * \brief Updates the progress bar with a new percentage value
     * \param[in] new_percentage The new percentage value to display
     */
    void updateProgress(double new_percentage) {
        std::lock_guard<std::mutex> lock(mutex);
        current_segments = static_cast<int>(std::round(new_percentage / 100 * total_segments));
        redraw(false);
    }

private:
    int total_segments; 
    int current_segments;
    option::CharFrames chars;

    /**
     * \brief Redraws the progress bar
     * \details Clears the line, displays the progress label, and fills the bar with the correct number of filled and empty characters.
     * \param[in] is_final If true, prevents the output from being flushed, allowing the next line to overwrite the bar.
     */
    void redraw(bool is_final = false) {
        clearLine();
        std::cout << progress_label;
        for (int i = 0; i < current_segments; ++i) {
            std::cout << chars[1]; // Filled character
        }
        for (int i = current_segments; i < total_segments; ++i) {
            std::cout << chars[0]; // Empty character
        }
        if (!is_final) {
            std::cout << std::flush;
        }
    }
};

/**
 * \class ProgressSpinner
 * \brief Class for displaying a spinning character as a progress indicator.
 * \details This class visually represents ongoing processes through a cyclic animation of characters.
 */
class ProgressSpinner : public ProgressIndicator {
public:
    /**
     * \brief Constructor for ProgressSpinner.
     * \param[in] progress_label Initial text displayed as the progress label.
     * \param[in] completed_label Text displayed upon completion.
     * \param[in] char_frames Characters used to represent the spinner.
     * \param[in] update_interval_ms Interval between frame updates in milliseconds.
     */
    ProgressSpinner(const ProgressSpinnerOptions& options = ProgressSpinnerOptions())
        : ProgressIndicator(options.progress_label, options.completed_label),
          chars(options.chars),
          keep_alive(true),
          update_interval_ms(options.update_interval_ms) {
            if (chars.empty()) {
                throw std::invalid_argument("Char frames vector may not be empty.");
            }
          }

    ~ProgressSpinner() {
        stop();
    }    

    /**
     * \brief Starts the spinner thread.
     * \details Sets the keep_alive flag to true and starts the spinner thread.
     */
    void start() override {
        showCursor(false);
        spinner_thread = std::thread(&ProgressSpinner::run, this);
    }

    /**
     * \brief Stops the spinner thread.
     * \details Sets the keep_alive flag to false and waits for the spinner thread to finish.
     */
    void stop() override {
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (stopped) {
                return; // Already stopped, do nothing
            }
            stopped = true;
            keep_alive = false;
        }
        if (spinner_thread.joinable()) {
            spinner_thread.join();
        }
        {
            std::lock_guard<std::mutex> lock(mutex);
            clearLine();
            std::cout << "\r" << progress_label << completed_label << std::endl;
            showCursor(true);
        }
    }

    size_t getCharCount() const { return chars.size(); }

private:
    option::CharFrames chars;
    std::atomic<bool> keep_alive;
    std::thread spinner_thread;
    int update_interval_ms = 100;
    bool stopped = false;

    void run() {
        size_t index = 0;
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(update_interval_ms));
            {
                std::lock_guard<std::mutex> lock(mutex);
                if (!keep_alive) {
                    break;
                }
                std::cout << "\r" << progress_label << chars[index] << std::flush;
            }
            index = (index + 1) % chars.size();
        }
    }
};

#endif // PROGRESS_INDICATOR_HPP

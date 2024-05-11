//      ____                                          _____       _                      
//     / __ \_________  ____ _________  __________   / ___/____  (_)___  ____  ___  _____
//    / /_/ / ___/ __ \/ __ `/ ___/ _ \/ ___/ ___/   \__ \/ __ \/ / __ \/ __ \/ _ \/ ___/
//   / ____/ /  / /_/ / /_/ / /  /  __(__  |__  )   ___/ / /_/ / / / / / / / /  __/ /    
//  /_/   /_/   \____/\__, /_/   \___/____/____/   /____/ .___/_/_/ /_/_/ /_/\___/_/     
//                   /____/                            /_/                               
#ifndef PROGRESS_INDICATOR_HPP
#define PROGRESS_INDICATOR_HPP

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>
#include <string>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#endif

/** 
 * @brief Toggle the visibility of the console cursor.
 * @param flag True to show the cursor, false to hide it.
 */
void showCursor(bool flag);

/**
 * @class ProgressIndicator
 * @brief Abstract base class for displaying progress indicators.
 */
class ProgressIndicator {
public:
    /**
     * @brief Constructor for ProgressIndicator.
     * @param progress_label Initial text displayed as the progress label.
     * @param completed_label Text displayed upon completion.
     */
    ProgressIndicator(const std::string& progress_label = "Progress: ",
                      const std::string& completed_label = " ✓ OK!")
    : progress_label(progress_label),
      completed_label(completed_label) {}

    virtual ~ProgressIndicator() = default;

    virtual void start() = 0;
    virtual void stop() = 0;

    /**
     * @brief Updates the text of the progress label.
     * @param new_text New text to set as the progress label.
     */
    virtual void updateText(const std::string& new_text) {
        std::lock_guard<std::mutex> lock(mutex);
        progress_label = new_text;
    }

protected:
    std::string progress_label, completed_label;
    std::mutex mutex;

    static void showCursor(bool showFlag) {
        #ifdef _WIN32
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = showFlag; // Set cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        #else
        std::cout << (showFlag ? "\033[?25h" : "\033[?25l");
        #endif
    }
};

/**
 * @class VProgressBar
 * @brief Class for displaying a progress bar.
 * @details This class provides a visual representation of progress through a single-character vertically-filling bar.
 */
class VProgressBar : public ProgressIndicator {
public:
    VProgressBar(const std::string& progress_label = "Progress: ",
                 const std::string& completed_label = " ✓ OK!",
                 const std::vector<std::string>& char_frames = {" ", "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"})
    : ProgressIndicator(progress_label, completed_label), chars(char_frames), current_percentage(0.0) {
        if (chars.empty()) {
            throw std::invalid_argument("VProgressBar chars cannot be empty");
        }
        tick = 100.0 / (chars.size() - 1);  // Adjust tick calculation to map the full range of characters
        SetConsoleOutputCP(CP_UTF8);
        showCursor(false);
        redraw();  // Initial draw
    }

    void start() override {}

    void stop() override {
        std::cout << "\r\033[K" << progress_label << completed_label << std::endl;
        showCursor(true);
    }

    void updateProgress(double new_percentage) {
        std::lock_guard<std::mutex> lock(mutex);
        if (new_percentage >= 100.0 - tick) {
            new_percentage = 100.0; // Automatically set to 100 if close enough
            if (!completed) {
                completed = true; // Mark completion to prevent multiple messages
            } else {
                return; // Skip updating if already completed
            }
        }
        current_percentage = new_percentage;
        redraw();
        if (current_percentage >= 100.0) {
            std::cout << "\r\033[K" << progress_label << completed_label << std::endl;
            showCursor(true);
        }
    }

    double getCurrentPercentage() const { return current_percentage; }
    size_t getCharCount() const { return chars.size(); }
    double getTick() const { return tick; }

private:
    bool completed = false;
    std::vector<std::string> chars;
    double current_percentage;
    double tick;

    void redraw() {
        std::cout << "\r\033[K" << progress_label; // Clear the line
        size_t index = static_cast<size_t>((current_percentage / 100.0) * (chars.size() - 1));
        std::cout << chars[index] << std::flush; // Display the current character
    }
};

/**
 * @class HProgressBar
 * @brief Class for displaying a horizontal progress bar using block characters.
 * @details This class visually represents progress through a customizable horizontal bar made up of block characters.
 */
class HProgressBar : public ProgressIndicator {
public:
    HProgressBar(const std::string& progress_label = "Progress: ",
                 const std::string& completed_label = " ✓ OK!",
                 int total_segments = 30,
                 const std::string& empty_char = "░",
                 const std::string& filled_char = "█")
    : ProgressIndicator(progress_label, completed_label),
      total_segments(total_segments),
      empty_char(empty_char),
      filled_char(filled_char),
      current_segments(0) {
        SetConsoleOutputCP(CP_UTF8);
        showCursor(false);
    }

    void start() override {
        updateProgress(0); // Initialize progress bar
    }

    void stop() override {
        std::lock_guard<std::mutex> lock(mutex);
        current_segments = total_segments; // Ensure bar is full
        redraw(true); // Redraw one last time with full progress
        std::cout << "\r\033[K"; // Clear any remaining characters and ensure the line is completely clean
        std::cout << progress_label << completed_label << std::endl;
        showCursor(true);
    }

    void updateProgress(double new_percentage) {
        std::lock_guard<std::mutex> lock(mutex);
        current_segments = static_cast<int>(std::round(new_percentage / 100 * total_segments));
        redraw(false);
    }

private:
    int total_segments;
    int current_segments;
    std::string empty_char, filled_char;

    void redraw(bool isFinal = false) {
        std::cout << "\r\033[K" << progress_label;
        for (int i = 0; i < current_segments; ++i) {
            std::cout << filled_char;
        }
        for (int i = current_segments; i < total_segments; ++i) {
            std::cout << empty_char;
        }
        if (!isFinal) {
            std::cout << std::flush;
        }
    }
};

/**
 * @class ProgressSpinner
 * @brief Class for displaying a spinning character as a progress indicator.
 * @details This class visually represents ongoing processes through a cyclic animation of characters.
 */
class ProgressSpinner : public ProgressIndicator {
public:
    /**
     * @brief Constructor for ProgressSpinner.
     * @param progress_label Initial text displayed as the progress label.
     * @param completed_label Text displayed upon completion.
     * @param char_frames Characters used to represent the spinner.
     */
    ProgressSpinner(const std::string& progress_label = "Progress: ",
                    const std::string& completed_label = " ✓ OK!",
                    const std::vector<std::string>& char_frames = {"|", "/", "-", "\\"})
    : ProgressIndicator(progress_label),
      chars(char_frames),
      keep_alive(true) {
        SetConsoleOutputCP(CP_UTF8);
        if (chars.empty()) {
            throw std::invalid_argument("Spinner chars cannot be empty");
        }
        showCursor(false);
    }

    void start() override {
        spinner_thread = std::thread(&ProgressSpinner::run, this);
    }

    void stop() override {
        keep_alive = false;
        if (spinner_thread.joinable()) {
            spinner_thread.join();
        }
        std::cout << "\r" << progress_label << completed_label << std::endl;
        showCursor(true);
    }

    size_t getCharCount() const { return chars.size(); }

private:
    std::vector<std::string> chars;
    std::atomic<bool> keep_alive;
    std::thread spinner_thread;

    void run() {
        size_t index = 0;
        while (keep_alive) {
            std::cout << "\r" << progress_label << chars[index] << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            index = (index + 1) % chars.size();
        }
    }
};

#endif // PROGRESS_INDICATOR_HPP

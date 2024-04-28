//      ____                                          _____       _                      
//     / __ \_________  ____ _________  __________   / ___/____  (_)___  ____  ___  _____
//    / /_/ / ___/ __ \/ __ `/ ___/ _ \/ ___/ ___/   \__ \/ __ \/ / __ \/ __ \/ _ \/ ___/
//   / ____/ /  / /_/ / /_/ / /  /  __(__  |__  )   ___/ / /_/ / / / / / / / /  __/ /    
//  /_/   /_/   \____/\__, /_/   \___/____/____/   /____/ .___/_/_/ /_/_/ /_/\___/_/     
//                   /____/                            /_/                               
//
// Lightweight progress indicator library for C++
// Developed by Chad with assistance from:
//     - ChatGPT versions 3.5 (Codeium) and 4

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <vector>
#include <string>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#endif

void showCursor(bool showFlag);

class ProgressBar {
public:
    /**
     * Constructor for the ProgressBar class. Initializes a progress bar with the given label and progress characters.
     *
     * @param label the label for the progress bar (default: "Progress: ")
     * @param progress_chars the characters to be used for the progress bar (default: {" ", "▂", "▃", "▄", "▅", "▆"})
     *
     * @throws std::invalid_argument if progress_chars is empty
     */
    explicit ProgressBar(   const std::string& label = "Progress: ",
                            const std::vector<std::string>& progress_chars = { " ", "▂", "▃", "▄", "▅", "▆" })
        : chars(progress_chars),        // Characters for the progress bar
          text(label),                  // Store the custom label
          current_percentage(0) {       // Store the current percentage value
        if (chars.empty()) {
            throw std::invalid_argument("ProgressBar: progress_chars cannot be empty");
        }
        std::cout << text << std::flush;  // Initialize the progress bar frame
    }

    /**
     * Updates the progress of the ProgressBar.
     *
     * @param new_percentage the new percentage value for the ProgressBar
     *
     * @throws std::out_of_range if the new_percentage is not in the range 0-100% [0.0, 100.0]
     */
    void updateProgress(double new_percentage) {
        showCursor(false);
        if (new_percentage < 0.0 || new_percentage > 100.0) {
            throw std::out_of_range("ProgressBar: new_percentage must be in the range [0.0, 100.0]");
        }
        current_percentage = new_percentage;
        redraw();
    }
    
    void addProgress(double increment) {
        updateProgress(current_percentage + increment);
    }

    void complete() {
        updateProgress(100.0);
        std::cout << "✓ OK!" << std::endl;
        showCursor(true);
    }

    double getCurrentPercentage() const {
        return current_percentage;
    }

private:
    const std::vector<std::string> chars;   // Characters for the progress bar
    const std::string text;                 // Store the custom label
    double current_percentage;               // Store the current percentage value

    /**
     * Redraws the progress bar with the updated percentage value.
     *
     * This function calculates the index of the character to display based on the current percentage value.
     * It then uses the index to select the appropriate character from the `chars` vector.
     * The selected character and any remaining characters are then printed to the console.
     *
     * @throws std::out_of_range if the calculated index is out of range of the `chars` vector size
     */
    void redraw() {
        int index = static_cast<int>(std::round((chars.size() - 1) * (current_percentage / 100.0)));
        if (index < 0 || index >= static_cast<int>(chars.size())) {
            throw std::out_of_range("ProgressBar: index out of range");
        }
        std::cout << "\r"
                  << "\033[2K"
                  << text << chars[index] << ' ' << std::string(chars.size() - index - 1, ' ') 
                  << std::flush;
    }
};

class ProgressSpinner {
public:
    /**
     * Constructor for the ProgressSpinner class.
     *
     * @param label The label for the spinner (default: "Progress")
     * @param padding The padding for the spinner (default is a single whitespace)
     * @param spinner_chars The characters to be used for the spinner (default:
     *        {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"})
     *
     * @throws None
     */
    explicit ProgressSpinner(   const std::string& label = "Progress",
                                const std::vector<std::string>& spinner_chars = {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"},
                                const std::string& padding = " ")
        : spinner(spinner_chars),               // Store the custom spinner characters
          text(label),                          // Store the custom label
          num_phases(spinner_chars.size()),     // Store the number of spinner phases
          keep_alive(true),                     // Initialize keep_alive flag to true
          padding(padding) {                    // Store the custom padding
    }

        /**
         * Starts the progress spinner.
         *
         * This function initializes the progress spinner by hiding the cursor and
         * creating a new thread to run the spinner animation.
         *
         * @throws None
         */
    void start() {
        showCursor(false);
        spinner_thread = std::thread(&ProgressSpinner::run, this);
    }

    /**
     * Stops the progress spinner.
     *
     * @throws None
     */
    void stop() {
        keep_alive = false;
        if (spinner_thread.joinable()) {
            spinner_thread.join();
        }
        showCursor(true);
        // Clear only the spinner part, not the label text
        std::cout << "\r" << text << ":" << std::string(padding.length(), ' ') << "✓ OK!" << std::endl;
    }

    // Method to update the text dynamically
    void updateText(const std::string& new_text) {
        text = new_text;
    }

private:
    std::vector<std::string> spinner;
    std::string text;  // Text displayed next to the spinner
    std::string padding;  // Padding between the text and the spinner
    size_t num_phases;
    std::atomic<bool> keep_alive;
    std::thread spinner_thread;

    void run() {
        while (keep_alive) {
            for (size_t i = 0; i < num_phases && keep_alive; i++) {
                std::cout << "\r" << text << ":" << padding << spinner[i] << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }
};

#ifdef _WIN32
void showCursor(bool showFlag) {
    if (showFlag) {
        std::cout<<"\033[?25h";
    } else {
        std::cout<<"\033[?25l";
    }
}
#else
void showCursor(bool showFlag) {
    if (showFlag) {
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = true;
        SetConsoleCursorInfo(out, &cursorInfo);
    }
}
#endif
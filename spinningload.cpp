#include "include/progress_spinner/progress_spinner.hpp"  // Include your custom header file
#include <iostream>
#include <vector>
#include <thread>  // Required for std::this_thread::sleep_for

int main() {

    std::cout << "HProgressBar Demo:\n";

    HProgressBar hp_bar;

    // Simulate a task that gradually completes, completing once a value of 100 is reached
    hp_bar.start();
    for (int i = 0; i <= 100; i += 5) {
        hp_bar.updateProgress(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Simulate time-consuming operations
    }
    hp_bar.stop();

    std::cout << "\nVProgressBar Demo:\n";
    // Construct a Progress Bar with default labels and progress characters
    VProgressBar pBar;
    // Simulate a task that gradually completes, completing once a value of 100 is reached
    
    double tick = pBar.getTick();
    for (double i = 0; i <= 100; i += tick) {
        pBar.updateProgress(i);  // Update progress
        if (i >= 50) {
            pBar.updateText("Halfway there: ");  // Update the progress text mid-operation
            continue;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Wait to simulate work
    }

    // Construct a Progress Bar with custom labels and progress characters
    VProgressBar custom_pBar("Working: ", " ✓ OK!", { "⣀", "⣄", "⣤", "⣦", "⣶", "⣷", "⣿" });

    tick = custom_pBar.getTick();
    for (double  i = 0.0; i <= 100.0; i += tick) {
        custom_pBar.updateProgress(i);  // Update progress
        if (i >= 40.0) {
            custom_pBar.updateText("Getting close: ");  // Update the progress text mid-operation
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Wait to simulate work
    }

    std::cout << "\nProgressSpinner Demo:\n";

    // Construct a Progress Spinner with default labels and progress characters
    ProgressSpinner spinner;

    spinner.start();
    for (unsigned short i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    spinner.stop();

    // Construct a Progress Spinner with custom labels and progress characters
    ProgressSpinner custom_spinner("Working: ", " ✓ OK!", { "⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏" });

    custom_spinner.start();
    for (unsigned short i = 0; i < 10; ++i) {
        if (i == 5) {
            custom_spinner.updateText("Halfway there: ");  // Update the progress label text mid-operation
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    custom_spinner.stop();

    return 0;
}

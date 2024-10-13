// spinningload.cpp
#include "progress_spinner/progress_indicators.hpp"  // Include your custom header file
#include <iostream>
#include <thread>  // Required for std::this_thread::sleep_for
#include <chrono>  // Required for std::chrono::milliseconds

int main() {
    std::cout << "HProgressBar Demo:\n";

    // Create options for HProgressBar
    HProgressBarOptions hp_options(
        option::Label{"Loading: "},
        option::CompletedLabel{"✓ OK!"},
        option::NumOfSegments{30},
        option::CharFrames{"-", "#"}  
    );

    HProgressBar hp_bar(hp_options);

    // Simulate a task that gradually completes
    hp_bar.start();
    for (int i = 0; i <= 100; i += 2) {
        hp_bar.updateProgress(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulate time-consuming operations
    }
    hp_bar.stop();

    std::cout << "\nVProgressBar Demo:\n";

    // Construct a VProgressBar with default options
    VProgressBar pBar;

    // Simulate a task that gradually completes
    double tick = pBar.getTick();
    for (double i = 0; i <= 100; i += tick) {
        pBar.updateProgress(i);  // Update progress
        std::this_thread::sleep_for(std::chrono::milliseconds(750));  // Wait to simulate work
    }

    // Construct a VProgressBar with custom, "dot-style" progress bar
    VProgressBarOptions vbar_options(
        option::Label{"Progress: "},
        option::CompletedLabel{"✓ OK!"},
        option::CharFrames{" ", "⣀", "⣄", "⣤", "⣦", "⣶", "⣷", "⣿" }  
    );

    VProgressBar custom_pBar(vbar_options);

    tick = custom_pBar.getTick();
    for (double i = 0.0; i <= 100.0; i += tick) {
        custom_pBar.updateProgress(i);  // Update progress
        if (i >= 40.0) {
            custom_pBar.updateText("Getting close: ");  // Update the progress text mid-operation
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(400));  // Wait to simulate work
    }
    custom_pBar.stop();

    std::cout << "\nProgressSpinner Demo:\n";

    // Construct a ProgressSpinner with default options
    ProgressSpinner spinner;

    spinner.start();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    spinner.stop();

    // Construct a ProgressSpinner with custom options
    ProgressSpinnerOptions spinner_options(
        option::Label{"Working: "},
        option::CompletedLabel{" ✓ OK!"},
        option::CharFrames{"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"},  
        option::UpdateIntervalMs{100}
    );

    ProgressSpinner custom_spinner(spinner_options);

    custom_spinner.start();
    for (unsigned short i = 0; i < 10; ++i) {
        if (i == 5) {
            custom_spinner.updateText("Halfway there: ");  // Update the progress label text mid-operation
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    custom_spinner.stop();

    // Another example using emoji characters
    ProgressSpinnerOptions spinner_options2(
        option::Label{"Working: "},
        option::CompletedLabel{" ✓ OK!"},
        option::CharFrames{"🌒", "🌓", "🌔", "🌕", "🌖", "🌗", "🌘"},  
        option::UpdateIntervalMs{500}
    );

    ProgressSpinner custom_spinner2(spinner_options2);

    custom_spinner2.start();
    for (unsigned short i = 0; i < 10; ++i) {
        if (i == 5) {
            custom_spinner2.updateText("Halfway there: ");  // Update the progress label text mid-operation
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    custom_spinner2.stop();

    ProgressSpinnerOptions spinner_options3(
        option::Label{"Working: "},
        option::CompletedLabel{" ✓ OK!"},
        option::CharFrames{"⠁", "⠂", "⠄", "⡀", "⢀", "⠠", "⠐", "⠈"},  
        option::UpdateIntervalMs{100}
    );

    ProgressSpinner custom_spinner3(spinner_options3);

    custom_spinner3.start();
    for (unsigned short i = 0; i < 10; ++i) {
        if (i == 5) {
            custom_spinner3.updateText("Halfway there: ");  // Update the progress label text mid-operation
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    custom_spinner3.stop();

    return 0;
}
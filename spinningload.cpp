//              _           _           __             __             
//    ___ ___  (_)__  ___  (_)__  ___ _/ /__  ___ ____/ /_______  ___ 
//   (_-</ _ \/ / _ \/ _ \/ / _ \/ _ `/ / _ \/ _ `/ _  // __/ _ \/ _ \
//  /___/ .__/_/_//_/_//_/_/_//_/\_, /_/\___/\_,_/\_,_(_)__/ .__/ .__/
//     /_/                      /___/                     /_/  /_/    
//
// A quick test program to show how to use the Progress Spinner library
#include "include/progress_spinner/progress_spinner.hpp"  // Include your custom header file
#include <iostream>
#include <vector>
#include <thread>  // Required for std::this_thread::sleep_for

int main() {
    std::cout << "HProgressBar Demo:\n";

    // Construct an HProgressBar (horizontal progress bar) with default labels and progress characters
    // Then, simulate a task that gradually completes
    HProgressBar hp_bar;

    hp_bar.start();
    for (int i = 0; i <= 100; i += 5) {
        hp_bar.updateProgress(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    hp_bar.stop();

    std::cout << "\nVProgressBar Demo:\n";

    // Now, let's construct a VProgressBar (vertical progress bar)
    VProgressBar pBar;
    
    double tick = pBar.getTick();
    for (double i = 0; i <= 100; i += tick) {
        pBar.updateProgress(i);  // Update progress
        /* if (i >= 40) {
            pBar.updateText("About halfway there: ");  // Update the progress text mid-operation
            continue;
        } */
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // Construct a custom vProgressBar with custom labels and progress characters
    VProgressBar custom_pBar(
        "Working: ", // Initial text
        " ✓ OK!", // Completed text
        { "⣀", "⣄", "⣤", "⣦", "⣶", "⣷", "⣿" } // Progress characters
    );

    tick = custom_pBar.getTick();
    for (double  i = 0.0; i <= 100.0; i += tick) {
        custom_pBar.updateProgress(i);
        if (i >= 40.0) {
            custom_pBar.updateText("Getting close: ");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "\nProgressSpinner Demo:\n";

    // Construct a ProgressSpinner with default labels and progress characters
    // Then, simulate a task that gradually completes
    ProgressSpinner spinner;

    spinner.start();
    for (unsigned short i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    spinner.stop();

    // Construct a ProgressSpinner with custom labels and progress characters
    ProgressSpinner custom_spinner(
        "Working: ", // Initial text
        " ✓ OK!", // Completed text
        { "⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏" }, // Progress characters
        100 // Update interval in milliseconds
    );

    custom_spinner.start();
    for (unsigned short i = 0; i < 10; ++i) {
        if (i == 5) {
            custom_spinner.updateText("Halfway there: ");  // Update the progress label text mid-operation
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    custom_spinner.stop();

    // Construct progress spinner with emojis
    ProgressSpinner custom_spinner2(
        "Working: ",
        " ✓ OK!",
        { "🌒", "🌓", "🌔", "🌕", "🌖", "🌗", "🌘" }
    );

    custom_spinner2.start();
    for (unsigned short i = 0; i < 10; ++i) {
        if (i == 5) {
            custom_spinner2.updateText("Halfway there: ");  // Update the progress label text mid-operation
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    custom_spinner2.stop();

    // Another example using different emoji chars
    ProgressSpinner custom_spinner3(
        "Working: ",
        " ✓ OK!",
        { "🕛", "🕐", "🕑", "🕒", "🕓", "🕔", "🕕", "🕖", "🕗", "🕘", "🕙", "🕚" }
    );

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

# Progress Indicators Library Usage Guide

This library provides a set of versatile progress indicators, perfect for displaying task completion in various forms. Here, you'll learn how to use three different progress indicators provided: **Horizontal Progress Bar (HProgressBar)**, **Vertical Progress Bar (VProgressBar)**, and **Spinner (ProgressSpinner)**. All are customizable to give you control over their visual appearance.

## 1. Horizontal Progress Bar (HProgressBar)

**HProgressBar** provides a simple way to display a progress bar that fills horizontally as the task progresses.

### Example Usage

```cpp
#include "include/progress_spinner/progress_spinner.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    HProgressBarOptions hp_options(
        option::Label{"Loading: "},
        option::CompletedLabel{"\u2713 OK!"},
        option::NumOfSegments{30},
        option::CharFrames{"-", "#"}
    );

    HProgressBar hp_bar(hp_options);
    hp_bar.start();
    for (int i = 0; i <= 100; i += 2) {
        hp_bar.updateProgress(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    hp_bar.stop();
}
```

### Customizing HProgressBar
- **Label**: Set the initial label (e.g., "Loading:").
- **CompletedLabel**: Specify the message to display upon completion (e.g., "\u2713 OK!").
- **NumOfSegments**: Set the total number of segments in the bar (default is 30).
- **CharFrames**: Define characters for empty and filled segments (e.g., `"-"`, `"#"`).

### How It Works
- The progress bar starts with `hp_bar.start()`.
- Use `hp_bar.updateProgress(int percentage)` to update the progress.
- `hp_bar.stop()` ends the bar and shows the completion message.

## 2. Vertical Progress Bar (VProgressBar)

**VProgressBar** displays progress using characters that fill vertically, simulating levels rising as the task completes.

### Example Usage

```cpp
#include "include/progress_spinner/progress_spinner.hpp"
#include <thread>
#include <chrono>

int main() {
    VProgressBar pBar;
    double tick = pBar.getTick();
    for (double i = 0; i <= 100; i += tick) {
        pBar.updateProgress(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
    pBar.stop();
}
```

### Customizing VProgressBar
- **Label**: Set the initial label (default is "Progress:").
- **CompletedLabel**: Specify a custom message on completion.
- **CharFrames**: Provide a series of characters representing various levels (e.g., `" "`, `"⣀"`, `"⣄"`, `"⣿"`).

### How It Works
- Call `pBar.updateProgress(double percentage)` to reflect task progression.
- Use `pBar.updateText(std::string new_label)` if you need to modify the label mid-operation.
- Finish with `pBar.stop()` to display the completion message.

## 3. Progress Spinner (ProgressSpinner)

**ProgressSpinner** is a rotating spinner, great for indicating tasks in progress when there's no specific percentage completion.

### Example Usage

```cpp
#include "include/progress_spinner/progress_spinner.hpp"
#include <thread>
#include <chrono>

int main() {
    ProgressSpinnerOptions spinner_options(
        option::Label{"Working: "},
        option::CompletedLabel{" \u2713 OK!"},
        option::CharFrames{"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"},
        option::UpdateIntervalMs{100}
    );

    ProgressSpinner spinner(spinner_options);
    spinner.start();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    spinner.stop();
}
```

### Customizing ProgressSpinner
- **Label**: Set the initial text for the spinner (e.g., "Working:").
- **CompletedLabel**: Define the message that will be displayed when complete (e.g., "\u2713 OK!").
- **CharFrames**: Customize the sequence of characters used to show the spinning effect (e.g., `"⠋"`, `"⠙"`, `"⠹"`, etc.).
- **UpdateIntervalMs**: Set how often the spinner frame updates (default is 100 ms).

### How It Works
- `spinner.start()` starts the spinner in a separate thread.
- Use `spinner.updateText(std::string new_label)` to change the label during spinning.
- `spinner.stop()` ends the spinner and displays the completion message.

## Putting It All Together

Here is how all of these components are used together in a single application:

```cpp
#include "include/progress_spinner/progress_spinner.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    // Horizontal Progress Bar Example
    std::cout << "HProgressBar Demo:\n";
    HProgressBarOptions hp_options(
        option::Label{"Loading: "},
        option::CompletedLabel{"\u2713 OK!"},
        option::NumOfSegments{30},
        option::CharFrames{"-", "#"}
    );
    HProgressBar hp_bar(hp_options);
    hp_bar.start();
    for (int i = 0; i <= 100; i += 2) {
        hp_bar.updateProgress(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    hp_bar.stop();

    // Vertical Progress Bar Example
    std::cout << "\nVProgressBar Demo:\n";
    VProgressBar pBar;
    double tick = pBar.getTick();
    for (double i = 0; i <= 100; i += tick) {
        pBar.updateProgress(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
    pBar.stop();

    // Spinner Example
    std::cout << "\nProgressSpinner Demo:\n";
    ProgressSpinner spinner;
    spinner.start();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    spinner.stop();
}
```

## Summary
- **HProgressBar** and **VProgressBar** are great for tracking tasks with a defined completion percentage.
- **ProgressSpinner** works well for indicating ongoing operations with uncertain durations.

All components are customizable, allowing users to craft their indicators to match their desired look and feel. Each progress indicator can be started, updated, and stopped, with options to change labels and characters to suit your needs.


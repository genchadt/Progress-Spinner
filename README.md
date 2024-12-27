# Progress Indicators Library

This C++ library provides a set of versatile progress indicators for displaying task completion in various forms within the console. It includes a **Horizontal Progress Bar (HProgressBar)**, a **Vertical Progress Bar (VProgressBar)**, and a **Spinner (ProgressSpinner)**. Each indicator is highly customizable, allowing you to control their visual appearance to match your application's aesthetic.

## Features

- **Horizontal Progress Bar (HProgressBar)**: Displays a traditional progress bar that fills horizontally.
- **Vertical Progress Bar (VProgressBar)**: Shows progress using characters that fill vertically, simulating rising levels.
- **Spinner (ProgressSpinner)**: A rotating spinner for indicating ongoing tasks without a specific completion percentage.
- **Customizable**: Options to change labels, completion messages, progress characters, and update intervals.
- **Thread-Safe**: Utilizes mutexes to ensure safe concurrent access to progress indicators.
- **Cross-Platform**: Supports both Windows and Unix-like systems with appropriate console handling.

## Prerequisites

- C++17 compatible compiler (GCC, Clang, MSVC, etc.)
- CMake 3.10 or higher
- Git (for cloning the repository)

## Installation

1. **Clone the repository:**

    ```bash
    git clone https://github.com/your-username/progress-indicator-library.git
    cd progress-indicator-library
    ```

    Replace `your-username` with your actual GitHub username or the appropriate repository URL.

2. **Build the library using CMake:**

    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

    This will generate the library and an example executable (`test_progress_indicator`).

## Usage

### 1. Horizontal Progress Bar (HProgressBar)

The `HProgressBar` provides a simple way to display a progress bar that fills horizontally as a task progresses.

#### Example Usage

```cpp
#include "progress_spinner/progress_indicators.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    HProgressBarOptions hp_options(
        option::Label{"Loading: "},
        option::CompletedLabel{"✓ OK!"},
        option::NumOfSegments{30},
        option::ProgressChars{"-", "#"},
        option::BracketChars{"[", "]"}
    );

    HProgressBar hp_bar(hp_options);
    hp_bar.start();
    for (int i = 0; i <= 100; i += 2) {
        hp_bar.updateProgress(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    hp_bar.stop();
    return 0;
}
```

#### Customizing HProgressBar

- **Label**: Set the initial label (e.g., "Loading: ").
- **CompletedLabel**: Specify the message to display upon completion (e.g., "✓ OK!").
- **NumOfSegments**: Set the total number of segments in the bar (default is 30).
- **ProgressChars**: Define characters for empty and filled segments (e.g., `"-"`, `"#"`) and optionally brackets (e.g., `["[", "]"]`).

#### How It Works

- The progress bar starts with `hp_bar.start()`.
- Use `hp_bar.updateProgress(int percentage)` to update the progress.
- `hp_bar.stop()` ends the bar and shows the completion message.

### 2. Vertical Progress Bar (VProgressBar)

The `VProgressBar` displays progress using characters that fill vertically, simulating levels rising as the task completes.

#### Example Usage

```cpp
#include "progress_spinner/progress_indicators.hpp"
#include <iostream>
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
    return 0;
}
```

#### Customizing VProgressBar

- **Label**: Set the initial label (default is "Progress: ").
- **CompletedLabel**: Specify a custom message on completion.
- **CharFrames**: Provide a series of characters representing various levels (e.g., `" "`, `"⣀"`, `"⣄"`, `"⣿"`).

#### How It Works

- Call `pBar.updateProgress(double percentage)` to reflect task progression.
- Use `pBar.updateText(std::string new_label)` to modify the label mid-operation.
- Finish with `pBar.stop()` to display the completion message.

### 3. Progress Spinner (ProgressSpinner)

The `ProgressSpinner` is a rotating spinner, ideal for indicating tasks in progress when there's no specific percentage completion.

#### Example Usage

```cpp
#include "progress_spinner/progress_indicators.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    ProgressSpinnerOptions spinner_options(
        option::Label{"Working: "},
        option::CompletedLabel{" ✓ OK!"},
        option::CharFrames{"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"},
        option::UpdateIntervalMs{100}
    );

    ProgressSpinner spinner(spinner_options);
    spinner.start();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    spinner.stop();
    return 0;
}
```

#### Customizing ProgressSpinner

- **Label**: Set the initial text for the spinner (e.g., "Working: ").
- **CompletedLabel**: Define the message displayed upon completion (e.g., " ✓ OK!").
- **CharFrames**: Customize the sequence of characters used to show the spinning effect (e.g., `"⠋"`, `"⠙"`, `"⠹"`, etc.).
- **UpdateIntervalMs**: Set how often the spinner frame updates (default is 100 ms).

#### How It Works

- `spinner.start()` starts the spinner in a separate thread.
- Use `spinner.updateText(std::string new_label)` to change the label during spinning.
- `spinner.stop()` ends the spinner and displays the completion message.

## Putting It All Together

Here is how all these components are used together in a single application, as demonstrated in `main.cpp`:

```cpp
#include "progress_spinner/progress_indicators.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    // Horizontal Progress Bar Example
    std::cout << "HProgressBar Demo:\n";
    HProgressBarOptions hp_options(
        option::Label{"Loading: "},
        option::CompletedLabel{"✓ OK!"},
        option::NumOfSegments{30},
        option::ProgressChars{"-", "#"},
        option::BracketChars{"[", "]"}
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

    // Custom Vertical Progress Bar Example
    VProgressBarOptions vbar_options(
        option::Label{"Progress: "},
        option::CompletedLabel{"✓ OK!"},
        option::CharFrames{" ", "⣀", "⣄", "⣤", "⣦", "⣶", "⣷", "⣿" }
    );
    VProgressBar custom_pBar(vbar_options);
    tick = custom_pBar.getTick();
    for (double i = 0.0; i <= 100.0; i += tick) {
        custom_pBar.updateProgress(i);
        if (i >= 40.0) {
            custom_pBar.updateText("Getting close: ");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
    custom_pBar.stop();

    // Spinner Example
    std::cout << "\nProgressSpinner Demo:\n";
    ProgressSpinner spinner;
    spinner.start();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    spinner.stop();

    // Custom Spinner Example
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
            custom_spinner.updateText("Halfway there: ");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    custom_spinner.stop();

    // Additional Spinner Examples with different character sets
    ProgressSpinnerOptions spinner_options2(
        option::Label{"Working: "},
        option::CompletedLabel{" ✓ OK!"},
        option::CharFrames{"🌒", "🌓", "🌔", "🌕", "🌖", "🌗", "🌘"},
        option::UpdateIntervalMs{200}
    );
    ProgressSpinner custom_spinner2(spinner_options2);
    custom_spinner2.start();
    for (unsigned short i = 0; i < 10; ++i) {
        if (i == 5) {
            custom_spinner2.updateText("Halfway there: ");
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
            custom_spinner3.updateText("Halfway there: ");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    custom_spinner3.stop();

    return 0;
}
```

## Summary

- **HProgressBar** and **VProgressBar** are excellent for tracking tasks with a defined completion percentage.
- **ProgressSpinner** is suitable for indicating ongoing operations with uncertain durations.

All components are customizable, allowing users to tailor their indicators to match their desired look and feel. Each progress indicator can be started, updated, and stopped, with options to change labels and characters to suit your needs.

## Contributing

Contributions to the Progress Indicators Library are welcome! Please feel free to fork the repository, make your changes, and submit a pull request.

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.

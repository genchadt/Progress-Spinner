# Progress Spinner

This C++ library offers a simple progress bar and spinner for console applications, providing a visual indicator of task progress. It is designed to be flexible and easy to use in various types of C++ projects.

## Features

- **Progress Bar**: Displays progress in percentage with customizable characters.
- **Spinner**: Shows an animated spinner for ongoing tasks without a defined end.

## Getting Started

### Prerequisites

- C++ compiler with C++11 support
- Windows or Linux operating system

### Installation

Clone this repository to your local machine using:

```bash
git clone https://github.com/your-username/progress-indicator-library.git

### Usage

Include the library in your project and create instances as needed.

ProgressBar Example:
```cpp
// Update the progress bar to 50%
ProgressBar progressBar("Loading: ");
progressBar.updateProgress(50.0);
progressBar.complete(); // Can also use progressBar.updateProgress(100.0); which calls complete()

// Update the progress bar additively until 100% is reached
ProgressBar.addProgress(10.0); // Adds 10% to current progress.```

ProgressSpinner Example:
```cpp
ProgressSpinner spinner("Processing");
spinner.start();
// Perform tasks...
spinner.stop();```

### Building and Running

```bash
g++ -std=c++11 -static-libgcc -static-libstdc++ -static -pthread -o spinningload spinningload.cpp ./spinningload```

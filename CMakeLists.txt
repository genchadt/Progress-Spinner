cmake_minimum_required(VERSION 3.10)
project(ProgressIndicatorLibrary)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Library source files
set(LIB_SOURCES
    src/progress_indicator.cpp
    src/v_progress_bar.cpp
    src/h_progress_bar.cpp
    src/progress_spinner.cpp
    src/options.cpp
    src/console.cpp
)

# Create the library
add_library(progress_indicator_lib ${LIB_SOURCES})

# Add the test executable
add_executable(spinningload build/spinningload.cpp)

# Link the library to the executable
target_link_libraries(spinningload PRIVATE progress_indicator_lib)

cmake_minimum_required(VERSION 3.10)
project(ProgressIndicatorLibrary)

# Set MinGW GCC as the compiler
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Compiler flags
if (MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static -pthread")
endif()

# Library source files
set(LIB_SOURCES
    src/progress_indicator.cpp
    src/v_progress_bar.cpp
    src/h_progress_bar.cpp
    src/progress_spinner.cpp
    src/options.cpp
    src/iconsole.cpp
)

# Check if all sources exist before adding the library
foreach(file ${LIB_SOURCES})
    if(NOT EXISTS ${CMAKE_SOURCE_DIR}/${file})
        message(FATAL_ERROR "Source file ${file} not found.")
    endif()
endforeach()

# Create the library
add_library(progress_indicator_lib ${LIB_SOURCES})

# Example or test executable
add_executable(test_progress_indicator test/main.cpp)

# Link the library to the executable
target_link_libraries(test_progress_indicator PRIVATE progress_indicator_lib)

# Platform-specific settings for Windows
if (WIN32)
    target_compile_definitions(progress_indicator_lib PRIVATE _WIN32_WINNT=0x0600)
endif()

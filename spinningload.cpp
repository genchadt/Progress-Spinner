//                                                                        
//             /           /           /              |                   
//   ___  ___    ___  ___    ___  ___ (  ___  ___  ___|     ___  ___  ___ 
//  |___ |   )| |   )|   )| |   )|   )| |   )|   )|   )    |    |   )|   )
//   __/ |__/ | |  / |  / | |  / |__/ | |__/ |__/||__/     |__  |__/ |__/ 
//       |                       __/                   -        |    |    
//
// A quick test of spinning progress indicator library for C++.
// Developed by Chad with assistance from:
//     - ChatGPT versions 3.5 and 4

#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>
#include "./spinning_progress.hpp"

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);

    /*
    try {
        ProgressSpinner spinner;
        spinner.start();  // Start the spinner in a separate thread
        std::this_thread::sleep_for(std::chrono::seconds(5));  // Simulate long-running operation
        spinner.stop();  // Ensure spinner stops before object destruction

        ProgressSpinner dotSpinner({"◐", "◓", "◑", "◒"});
        dotSpinner.start();  // Start the spinner in a separate thread
        std::this_thread::sleep_for(std::chrono::seconds(5));  // Simulate another operation
        dotSpinner.stop();  // Ensure spinner stops before object destruction

        ProgressSpinner barSpinner({"▉", "▊", "▋", "▌", "▍", "▎", "▏", "▕"});
        barSpinner.start();  // Start the spinner in a separate thread
        std::this_thread::sleep_for(std::chrono::seconds(5));  // Simulate another operation
        barSpinner.stop();  // Ensure spinner stops before object destruction

        ProgressSpinner boxSpinner({"┤", "┘", "┴", "└", "├", "┌", "┬", "┐"});
        boxSpinner.start();  // Start the spinner in a separate thread
        std::this_thread::sleep_for(std::chrono::seconds(5));  // Simulate another operation
        boxSpinner.stop();  // Ensure spinner stops before object destruction

        ProgressSpinner meteorSpinner({"🌑", "🌒", "🌓", "🌔", "🌕", "🌖", "🌗", "🌘"});
        meteorSpinner.start();  // Start the spinner in a separate thread
        std::this_thread::sleep_for(std::chrono::seconds(5));  // Simulate another operation
        meteorSpinner.stop();  // Ensure spinner stops before object destruction

        ProgressSpinner clockSpinner({"🕐", "🕑", "🕒", "🕓", "🕔", "🕕", "🕖", "🕗", "🕘", "🕙", "🕚", "🕛"});
        clockSpinner.start();  // Start the spinner in a separate thread
        std::this_thread::sleep_for(std::chrono::seconds(5));  // Simulate another operation
        clockSpinner.stop();  // Ensure spinner stops before object destruction

        ProgressSpinner lineSpinner({"|", "/", "—", "\\"});
        lineSpinner.start();  // Start the custom spinner
        std::this_thread::sleep_for(std::chrono::seconds(5));  // Simulate another operation
        lineSpinner.stop();  // Stop the custom spinner
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return -1;
    }
    */ 

    try {
        ProgressBar progressBar("Loading: ");
        ProgressBar progressBar2;
        ProgressBar progressBar3;

        // Simulate some work and update progress in percentages
        while (progressBar.getCurrentPercentage() < 100.0) {
            progressBar.addProgress(20);  // Increment progress by 12.5%
            std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate some processing time
        }
        progressBar.complete();  // Ensure the progress bar is complete

        while (progressBar2.getCurrentPercentage() < 100.0) {
            progressBar2.addProgress(20);  // Increment progress by 12.5%
            std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate some processing time
        }
        progressBar2.complete();  // Ensure the progress bar is complete

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}

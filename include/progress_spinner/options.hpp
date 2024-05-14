#include <string>
#include <vector>

namespace option {
    struct number_of_segments
    {
        int number_of_segments;
    };
    
    struct update_interval_ms
    {
        int update_interval_ms;
    };

    struct spinner_chars
    {
        std::vector<std::string> spinner_chars = {"|", "/", "-", "\\"};
    };

    struct progress_bar_chars
    {
        std::vector<std::string> progress_bar_chars = {"░", "█"};
    };

    struct label
    {
        std::string progress_label = "Progress: ";
    };

    struct completed_label
    {
        std::string completed_label = " ✓ OK!";
    };
}
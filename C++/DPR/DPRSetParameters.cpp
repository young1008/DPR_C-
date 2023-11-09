#include <iostream>
#include <vector>
#include <string>
#include <map>

struct Options {
    double gain;
    int background;
    std::string temporal;
};

Options DPRSetParameters(double PSF, const std::map<std::string, std::string>& varargin) {
    Options options;

    options.gain = 1;
    options.background = static_cast<int>(10 * PSF);
    options.temporal = "";

    std::map<std::string, std::string> validOptions = {
        {"gain", "1"},
        {"background", std::to_string(static_cast<int>(10 * PSF))},
        {"temporal", ""}
    };

    for (const auto& item : varargin) {
        auto it = validOptions.find(item.first);
        if (it != validOptions.end()) {
            it->second = item.second;
        }
    }

    options.gain = std::stod(validOptions["gain"]);
    options.background = std::stoi(validOptions["background"]);
    options.temporal = validOptions["temporal"];

    return options;
}

int main() {
    double PSF = 2.0;  // Replace with the actual value of PSF
    std::map<std::string, std::string> varargin = {
        {"gain", "2"},
        {"background", "20"},
        {"temporal", "mean"}
    };

    Options result = DPRSetParameters(PSF, varargin);

    std::cout << "gain: " << result.gain << std::endl;
    std::cout << "background: " << result.background << std::endl;
    std::cout << "temporal: " << result.temporal << std::endl;

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>

int saveSpeedToTextFile(const std::string& speedValue, const std::string& filename) {
    std::ofstream outputFile(filename, std::ios_base::app); // Open in append mode

    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1; // Indicate an error
    }

    outputFile << speedValue << std::endl; // Write the speed to a new line

    outputFile.close();
    return 0; // Indicate success
}

int main() {
    std::string speedFromGUI = "80.7"; // Example speed value
    std::string textFilename = "speed_data.txt";

    int saveResult = saveSpeedToTextFile(speedFromGUI, textFilename);

    if (saveResult != 0) {
        std::cerr << "Failed to save speed." << std::endl;
    }
    else {
        std::cout << "Speed saved successfully." << std::endl;
    }

    return 0;
}
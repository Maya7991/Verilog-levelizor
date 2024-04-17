#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // For std::find

#include"customError.hpp"
#include"utils.hpp"
// #include "keywords.hpp"

std::string keywords[] = {  // Verilog keywords
    "module",
    "input",
    "output",
    "wire",
    "endmodule"
};



/**
 * Determines if a string is reserved keyword
 * @param the string to compare
 * @return whether the string is reserved or not
 */
bool reserved (const std::string& word)
{
    for (int i = 0; i < sizeof(keywords); i++)
        if (word == keywords[i])
            return true;
    return false;
}

/**
 * Determines if a string is gate
 * @param the string to check
 * @return whether the string is a gate or not
 */
bool gate (const std::string& word, std::vector<std::string>& gatelibrary)
{
    return std::find(gatelibrary.begin(), gatelibrary.end(), word) != gatelibrary.end();
}

std::string trim(const std::string& str) {
    size_t start = 0;
    size_t end = str.length() - 1;

    // Find the index of the first non-whitespace character from the start
    while (start <= end && std::isspace(str[start]))
        start++;

    // Find the index of the first non-whitespace character from the end
    while (end >= start && std::isspace(str[end]))
        end--;

    // Extract the trimmed substring
    return str.substr(start, end - start + 1);
}

bool isSpaceNext(const std::string& input) {
    size_t pos = input.find("INVX1");
    if (pos != std::string::npos && pos + 5 < input.size()) { // Check if "INVX1" is found and if there are characters after it
        char nextChar = input[pos + 5]; // Get the character after "INVX1"
        return (nextChar == ' '); // Check if it's a space
    }
    return false; // "INVX1" not found or no character after it
}

void printGates(const std::vector<Gate>& gates) {
    for (const auto& gate : gates) {
        std::cout << "Name: " << gate.name << std::endl;
        std::cout << "Type: " << gate.type << std::endl;
        std::cout << "Inputs:";
        for (const auto& input : gate.inputs) {
            std::cout << " " << input << ",";
        }
        std::cout << std::endl;
        std::cout << "Output: " << gate.output << std::endl;
        std::cout << "Level: " << gate.level << std::endl;
        std::cout << std::endl;
    }
}
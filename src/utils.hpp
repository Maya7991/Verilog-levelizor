#include <cstring> // For strcmp
#include <cstdlib> // For NULL definition
#include <string>
#include <fstream>
#include <iostream>

struct Gate {
    std::string name;
    std::string type;
    std::vector<std::string> inputs;
    std::string output;
    int level;
};


/**
 * stores the name of Gates used in the library
 * @param the filename containing gates separated by newline
 * @return void
 */
void storeGateInformation (const std::string& filename);

/**
 * Determines if a string is reserved keyword
 * @param the string to compare
 * @return whether the string is reserved or not
 */
bool reserved (const std::string& word);

/**
 * Determines if a string is gate
 * @param the string to check
 * @param vector holding the gate names used in library
 * @return whether the string is a gate or not
 */
bool gate (const std::string& word, std::vector<std::string>& gatelibrary);

/**
 * Removes trailing white spaces from left and right side of string
 * @param the string to trim
 * @return trimmed string
 */
std::string trim(const std::string& str);

void printGates(const std::vector<Gate>& gates);

void printLevelizedGates(const std::vector<Gate>& gates, int max_level);
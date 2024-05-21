#ifndef TREENOR
#define TREENOR

#include<string>
#include<vector>


struct Gate {
    std::string name;
    std::string type;
    std::vector<std::string> inputs;
    std::string output;
    bool pi;
    bool po;
    int level;

    std::vector<Gate*> children;

    Gate(){};
    Gate(std::string n, std::string t) : name(n), type(t) {}

    // Method to get information about the gate
    std::string getInfo() const {
        std::string info = "Name: " + name + ", Type: " + type + ", Inputs: [";
        for (const auto& input : inputs) {
            info += input + ", ";
        }
        info += "], Output: " + output + ", PO: " + (po ? "true" : "false");
        return info;
    }
};

struct Netlist{
    std::string verilogfilename;
    std::vector<std::string> pi;
    std::vector<std::string> po;
    std::vector<Gate*> po_gates;
    std::vector<Gate*> gates;

    Netlist(){};
};

#endif
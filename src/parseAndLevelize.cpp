#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include"datatypes.hpp"
#include"customError.hpp"
#include"utils.hpp"

class VerilogParser {
    private:
        std::string verilogfilename, gatefilename;
        std::vector<std::string> gatelibrary;
        Netlist netlist;
        std::string line;
        int line_number= 0;

        void parseLine(const std::string& line) {
            std::istringstream iss(line);
            std::string token;
            iss >> token;
            line_number++;
            token = trim(token);

            if("//" == token) {
                return;
            }

            if(token=="input"){
                std::string inputs;
                while (std::getline(iss, inputs, ',')) {
                    netlist.pi.push_back(trim(inputs));
                }
            }

            if(token=="output"){
                std::string outputs;
                while (std::getline(iss, outputs, ',')) {
                    netlist.po.push_back(trim(outputs));
                }
            }
            
            if(gate(token, gatelibrary)){
                std::string gateName, gateType;
                size_t pos;
                gateType = token;
                
                iss >> token;
                // Extract gate name
                pos = token.find_first_of('(');
                if (std::string::npos == pos){
                   gateName=token;
                    iss >> token;
                } 
                else{
                    gateName = token.substr(0, pos);
                }

                Gate* gate = new Gate(gateName, gateType);

                // Extract inputs and outputs
                std::string::size_type firstParenPos = line.find('(');
                std::string::size_type lastParenPos = line.find_last_of(')');
                if (firstParenPos == std::string::npos && lastParenPos == std::string::npos) throw ce::CustomError(" Syntax error:: Missing Paranthesis \n Syntax error:: "+line);
                std::string content = line.substr(firstParenPos + 1, lastParenPos-firstParenPos- 1); // Extract content between parentheses
                
                // Tokenize content by commas
                std::istringstream contentIss(content);
                while (std::getline(contentIss, token, ',')) {
                    token= trim(token);
                    firstParenPos = token.find('(');
                    lastParenPos = token.find_last_of(')');
                    token = token.substr(firstParenPos + 1, lastParenPos - firstParenPos - 1);
                    gate->inputs.push_back(token);
                }
                gate->inputs.pop_back();// remove last toke from input as its the output
                gate->output = token;
                gate->level = -1;

                //create a vector of pointers with po gates. later used for constructing NOR tree
                for(const auto& idx: netlist.po){
                    if(gate->output == idx) netlist.po_gates.push_back(gate);
                }

                netlist.gates.push_back(gate);
            }
        }


        /**
         * stores the name of Gates used in the library
         * @param the filename containing gates separated by newline
         * @param vector holding the gate names used in library
         * @return void
         */
        void storeGateInformation (const std::string& filename){
            std::string line_buffer;
            std::ifstream file(filename);
            if (!file.is_open()) {
                throw ce::CustomError("Unable to open gate info file: "+filename);
            }
            while (std::getline(file, line_buffer)) {
                gatelibrary.push_back(trim(line_buffer)); // Store each line in the array
            }
            if(gatelibrary.empty()) throw ce::CustomError(filename+" file is empty. Unable to capture gate information.");
            std::cout<<"gatelibrary size: "<<gatelibrary.size()<< std::endl ; 
            file.close();
        }

    public:
    VerilogParser(const std::string& verilogfn, const std::string& gatefn){
        storeGateInformation(gatefn);
        netlist.verilogfilename = verilogfn;
        gatefilename = gatefn;

    }
    Netlist parseFile(){

        std::ifstream file(netlist.verilogfilename);
        if (file.is_open()) {
            try{
                while (std::getline(file, line, ';')) {
                    parseLine(trim(line));
                }
            }
            catch(ce::CustomError& e){
                throw e;
            }
            std::cout<<"line_number: " <<line_number << ", Gates: "<< netlist.gates.size() << std::endl<< std::endl;
            file.close();
        } else {
            throw ce::CustomError("Unable to open Verilog file: "+netlist.verilogfilename);
        }
        
        printParsedInfo(netlist);

        return netlist;

    }

    /**
     * Perform breadth-first search (BFS) traversal to levelize gates
     */
    void levelizeNetlist(){
        if(netlist.gates.empty()) throw ce::CustomError("No netlist available to perform levelization.");
        
        std::queue<Gate*> q; // Queue for BFS traversal
        int max_level = 0;

        std::unordered_set<std::string> primaryInputs(netlist.pi.begin(), netlist.pi.end());

        for (auto& gate : netlist.gates) {
            for (const auto& gate_input : gate->inputs) {
                // Check if gate's input is a primary input
                if (primaryInputs.find(gate_input) != primaryInputs.end()) {
                    gate->level = 0;
                    q.push(gate);
                    break;  // Break after finding the first primary input
                }
            }
        }

        // for (const auto& gate : netlist.gates) {
        //     bool isPrimaryInput = false;
        //     for(const auto& gate_input: gate.inputs){
        //         //check if gate's input is a primary input and initialize it to level 0              
        //         for (const auto& primaryInput : pi) {
        //             if(gate_input==primaryInput){
        //                 gate.level=0;
        //                 q.push(&gate);
        //                 isPrimaryInput = true;
        //                 break;
        //             }
        //         }
        //         if(isPrimaryInput) break;
        //     }
        // }

        // Perform BFS traversal
        while (!q.empty()) {
            Gate* currentGate = q.front();
            q.pop();

            // Update levels of gates connected to currentGate's inputs
            for (auto& gate : netlist.gates) {
                for (auto& input: gate->inputs){
                    if(currentGate->output == input && (gate->level == -1 || gate->level <= currentGate->level)){ // might have to remove 2nd condition
                        gate->level= currentGate->level + 1;
                        q.push(gate);
                        max_level = max_level<gate->level ? gate->level: max_level;
                    }
                }
            }
        }
        // std::cout<<"--------------------\n";
        // printGates(netlist.gates);
        // std::cout<<"--------------------\n";
        // printLevelizedGates(netlist.gates, max_level); // writes levelwise gate information to a log.txt

    }
};

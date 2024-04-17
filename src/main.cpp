
#include <iostream>
#include"parseAndLevelize.cpp"
// #include"parseError.hpp"

int main(int argc, char const *argv[])
{
    // Check if the user provided the correct number of arguments
    if (argc != 3) {
        std::cerr << std::endl << "Incorrect Usage!"<< std::endl;
        std::cerr << "Usage: " << argv[0] << " <verilog_file> <gate_info_file>" << std::endl << std::endl;
        return 1; // Return 1 to indicate incorrect usage
    }

    try{
        
        VerilogParser parser(argv[1], argv[2]);
        parser.parseFile(argv[1]);
        parser.levelizeNetlist();
    }catch (ce::CustomError& e) {
		std::cout << std::endl << "Error=> " << e.what() << std::endl << std::endl;
	}
    
    return 0;
}
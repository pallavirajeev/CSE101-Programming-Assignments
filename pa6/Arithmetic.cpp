//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa6
// Arithmetic.cpp
// Top Client File
//-----------------------------------------------------------------------------
#include "BigInteger.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

int main(int argc, char* argv[]){
	//if there are not three arguments then throw an error
    if(argc != 3){
        throw std::invalid_argument("Incorrect number of arguments. Usage: Arithmetic <input file> <output file>\n");
    }

    //initialize and declare variables

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    std::ifstream input(inputFile);
    std::ofstream output(outputFile);

    //check if the files can be opened if not throw an error
    if (!input.is_open()) {
        throw std::runtime_error("Error opening input file: " + inputFile);
    }

    if (!output.is_open()) {
        throw std::runtime_error("Error opening output file: " + outputFile);
    }

    	std::string line;

    	BigInteger A, B;

        // Read line 1 as BigInteger A
        if (std::getline(input, line)) {
            A = BigInteger(line);
        }

        // Skip line 2
        std::getline(input, line);

        // Read line 3 as BigInteger B
        if (std::getline(input, line)) {
            B = BigInteger(line);
        }

    // print out requested quantities
    
    // A
    output << (A) << std::endl << std::endl;
    
    // B
    output << (B) << std::endl << std::endl;
    
    // A + B
    output << (A + B) << std::endl << std::endl;
    
    // A - B
    output << (A - B) << std::endl << std::endl;
    
    // A - A
    output << (A - A) << std::endl << std::endl;
    
    // 3A - 2B
    output << ((3 * A) - (2 * B)) << std::endl << std::endl;
    
    // AB
    output << (A * B) << std::endl << std::endl;    
    
    // A^2
    output << (A * A) << std::endl << std::endl;
    
    // B^2
    output << (B * B) << std::endl << std::endl;
    
    // 9A^4 + 16B^5
    output << ((9 * (A * A * A * A)) + (16 * (B * B * B * B * B))) << std::endl << std::endl;



    // Close the input and output files
    input.close();
    output.close();

    return 0;
}
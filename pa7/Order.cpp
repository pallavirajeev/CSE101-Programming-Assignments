//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa7
// Dictionary.cpp
// Top Client File
//-----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Dictionary.h"

int main(int argc, char* argv[]){
	//if there are not three arguments then throw an error
    if(argc != 3){
        throw std::invalid_argument("Incorrect number of arguments. Usage: Order <input file> <output file>\n");
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

    //read lines and insert into dict
	Dictionary dict;
    std::string line;
    int lineNumber = 1;

    while(std::getline(input, line)){
        dict.setValue(line, lineNumber);
        lineNumber++;
    }

    //print out desired output
    output << dict.to_string() << "\n";

    //output << "\n";

    //keys in pre-order traversal order
    output << dict.pre_string() << "\n";

    dict.clear();
    // Close the input and output files
    input.close();
    output.close();

    return 0;

}
//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa8
// WordFrequency.cpp
// Second Top Client File
//-----------------------------------------------------------------------------

#include "Dictionary.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
	//initialize variables 
    size_t begin, end, len;
    ifstream in;
    ofstream out;
    string line, key;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    Dictionary dict;

    // check for correct number of arguments
    if(argc != 3){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return EXIT_FAILURE;
    }

    // open and check files
    in.open(argv[1]);
    if(!in.is_open()){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return EXIT_FAILURE;
    }

    out.open(argv[2]);
    if(!out.is_open()){
        cerr << "Unable to open file " << argv[2] << " for reading" << endl;
        return EXIT_FAILURE;
    }

    // read lines
    while(getline(in, line)){
        len = line.length();

        // get first key
        begin = min(line.find_first_not_of(delim, 0), len);
        end = min(line.find_first_of(delim, begin), len);
        key = line.substr(begin, (end - begin));

        while(key != ""){
            // convert to lower case:
            for(int i = 0; i < static_cast<int>(key.length()); i++){
                if(key[i] >= 'A' && key[i] <= 'Z'){
                key[i] = key[i] - 'A' + 'a'; // convert uppercase to lowercase
                }
            }

            // add keys to dictionary
            if(dict.contains(key)){
            	//if key already there then increment corresponding value 
                dict.getValue(key)++;
            }
            else{
            	//otherwise use setValue 
                dict.setValue(key, 1);
            }

            // get next key
            begin = min(line.find_first_not_of(delim, (end + 1)), len);
            end = min(line.find_first_of(delim, begin), len);
            key = line.substr(begin, (end - begin));
        }
    }

    out << dict << endl;
    
    //clear Dictionary
    dict.clear();

    //close the files
    in.close();
    out.close();

    return EXIT_SUCCESS;
}
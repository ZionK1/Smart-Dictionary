/******************************************************************************
 * Zion Kang, zkang5
 * 2023 Spring CSE101 PA8
 * Order.cpp
 * Order Program for pa8
 * ***************************************************************************/
#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char * argv[]){
    ifstream in;
    ofstream out;

    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // read input for Dictionary
    Dictionary Dict; 
    string curr; // use as string buffer
    int index = 1;
    while (getline(in, curr)) { // loop getting each line
        Dict.setValue(curr, index);
        index += 1;
    }

    // write to outfile
    out << Dict << endl;
    out << Dict.pre_string() << endl;

    return 0;
}
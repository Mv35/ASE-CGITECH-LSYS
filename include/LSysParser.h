#ifndef LSYSPARSER_H_
#define LSYSPARSER_H_

#include "LSys.h"
#include "LSysStruct.h"
#include "LSysStructForFile.h"

///@file LSysParser.h
/// @brief The text file parser used to obtain an l-system structure with the values passed from the file
/// class that will parse an accordingly formatted text file and
/// store the values in both a LSysStruct and LSysStructForFile
///Modified from : Robert J Yager "Reading, Writing and Parsing text files in C++"
/// [Accessed June 2017] Available from: www.dtic.mil/get-tr-doc/pdf?AD=ADA611850
//enum lsystype{D0L=0,S0L=1};
class LSysParser
{
public:

    ///constructor
    LSysParser();
    ///@brief method that parses a specified file and stores the according values into an LSysStruct and a
    /// LSysStructForFile data structure
    LSysStruct toParse(const char* file_name, LSysStruct &o_result, LSysStructForFile &lsys_parameters);
    //LSysStruct toParse(const char* file_name, LSysStruct &o_result);

    ///@brief method to get the input file
    std::string getInputFile();

    ///@brief method that iterates through an unordered_map of definitions and performs calculations so that
    /// the sum of the float values of the map are always 1.
    std::unordered_map<std::string, float> definitionsNormalization(std::unordered_map<std::string ,float> &defins);

    ///@brief method to get LSysType according to the l-system that has been parsed
    //int getLSysType(std::vector<ProductionRule> &Prules);

private:

    std::string m_inputfile;
};

#endif // LSYSPARSER_H

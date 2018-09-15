#ifndef LSYSPARSER_H_
#define LSYSPARSER_H_

#include "LSys.h"
#include "LSysStruct.h"
#include "LSysStructForFile.h"

///@file LSysParser.h
/// @brief class that will parse an accordingly formatted text file and
/// store the values in both a LSysStruct and LSysStructForFile

class LSysParser
{
public:
    //----------------------------------------------------------------------------------------------------------------------
    ///@brief constructor
    LSysParser();
    //----------------------------------------------------------------------------------------------------------------------
    ///@brief method that parses a specified file and stores the according values into an LSysStruct and a LSysStructForFile data structure
    /// @param _file_name the name of the file
    /// @param _o_result LSysStruct to store the resulting LSystem parameters
    /// @param _lsys_parameters LSysStructForFile to store the resulting LSystem parameters for file output and UI
    //----------------------------------------------------------------------------------------------------------------------
    LSysStruct toParse(const char* _file_name, LSysStruct &_o_result, LSysStructForFile &_lsys_parameters);
    //----------------------------------------------------------------------------------------------------------------------
    ///@brief method to get the input file
    //----------------------------------------------------------------------------------------------------------------------
    std::string getInputFile();
    //----------------------------------------------------------------------------------------------------------------------
    ///@brief method that iterates through an unordered_map of definitions and performs calculations so that
    /// the sum of the float values of the map are always 1.
    /// @param _defins unordered map of definition strings and respective float weight value
    //----------------------------------------------------------------------------------------------------------------------
    std::unordered_map<std::string, float> definitionsNormalization(std::unordered_map<std::string ,float> &_defins);

private:
    //----------------------------------------------------------------------------------------------------------------------
    ///@brief input file
    //----------------------------------------------------------------------------------------------------------------------
    std::string m_inputfile;
};

#endif // LSYSPARSER_H

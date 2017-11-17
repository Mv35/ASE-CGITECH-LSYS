#ifndef LSYSSTRUCTFORFILE_H
#define LSYSSTRUCTFORFILE_H

#include <string>
#include <vector>

#include "ProductionRule.h"

/// @file LSysStructForFile.h
/// @brief LSys data structure similar to LSysStruct
/// needed to store LSysStruct elements to easly print the element's values to a text file


struct LSysStructForFile
{
    ///same as LSysStruct but Prules is a vector of strings instead, easier to export to a file

    ///@brief axiom
    std::string axiom;
    ///@brief angle
    float angle;
    ///@brief iterations
    int iteration;
    ///@brief drawLenght
    float drawLenght;
    ///@brief constants
    std::vector<std::string> constants;
    ///@brief Prules vector
    std::vector<std::string> Prules;
    ///@brief LSys type
    int LSystype;


};


#endif // LSYSSTRUCTFORFILE_H

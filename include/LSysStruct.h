#ifndef LSYSSTRUCT_H_
#define LSYSSTRUCT_H_

#include "ProductionRule.h"

///@file LSYSSTRUCT_H_
///@brief the data structure to store the l-system element's values
/// all the values required for the creation of an L-system

struct LSysStruct
{
    ///@brief the axiom
    std::string axiom;

    ///@brief the angle
    float angle;

    ///@brief the iterations
    int iteration;

    ///@brief lenght of drawing
    float drawLenght;

    ///@brief vector of constants
    std::vector<std::string> constants;

    ///@brief vector of PruductionRules
    std::vector<ProductionRule> Prules;

    ///@brief type of l-system
    int LSysType;

    ///@brief parameters for the most basic form of L-systems
    /// also known as fibonacci L-system.
    /// default instantiation of the LSysStruct
    LSysStruct()
    {
        axiom="b";
        Prules.resize(2);
        Prules[0].key="a";
        Prules[0].definitions["ab"]=1.0f;
        Prules[1].key="b";
        Prules[1].definitions["a"]=1.0f;
        //iteration=0;
        //angle=0;
        //drawLenght=0;
    }

};

#endif //LSYSSTRUCT_H_

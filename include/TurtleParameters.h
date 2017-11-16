#ifndef TURTLEPARAMETERS_H_
#define TURTLEPARAMETERS_H_

///@file TurtleParameter.h
/// @brief parameter data structure used by the Turtle class in order to interpret the passed string.

struct TurtleParameters
{
    ///@brief angle
    float angle;
    ///@brief iteration
    int iteration;
    ///@brief drawLenght
    float drawLenght;
    ///@brief startX
    float startX = 0.0f;
    ///@brief startY
    float startY =0.0f;
    ///@brief startZ
    float startZ =0.0f;
    ///@brief dictSymbols
    std::vector<std::string> dictSymbols;
    ///@brief constants
    std::vector<std::string> constants;
    ///@brief lSys
    std::vector<std::string> lSys;
};
#endif // TURTLEPARAMETERS_H_

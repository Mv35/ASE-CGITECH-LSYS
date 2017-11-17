#ifndef TURTLE_H_
#define TURTLE_H_

#include <string>
#include <vector>
#include <ngl/Vec4.h>
#include <ngl/Transformation.h>
#include "TreeData.h"
#include "TurtleParameters.h"

///@file Turtle.h
/// @brief My turtle class will interpret the result of an L-System string iteration
///  based on it's dictionary/alphabet




class Turtle
{
private:

    ///@brief m-angle
    float m_angle;
    ///@brief m_step
    float m_step;
    ///@brief m_start_x
    float m_start_x;
    ///@brief m_start_y
    float m_start_y;
    ///@brief m_start_z
    float m_start_z;
    ///@brief m_constants
    std::vector<std::string> m_constants;
    ///@brief m_variables
    std::vector<std::string> m_variables;

protected:

    ///@brief m_lSys
    std::string m_lSys;
    ///@brief m_iteration
    unsigned m_iteration;
    ///@brief m_dictSymbols
    std::vector<std::string> m_dictSymbols;

public:

    //default constructor
    Turtle();
    //copy constructor taking an instance of the TurtleParameters Stuct
    Turtle(TurtleParameters p);

    //Default deconstructor
    ~Turtle(){std::cout<<"deconstructor called\n";}

    //Accessors
    float getIteration();
    float getAngleInRad();
    float getAngleInDeg();
    float getdrawStep();
    float getStartX();
    float getStartY();
    float getStartZ();

    //Mutators
    void setIteration(int);
    void setAngleInRad(float);
    void setAngleInDeg(float);
    void setdrawStep(float);
    void setStartX(float);
    void setStartY(float);
    void setStartZ(float);




    ///actual method that interprets the l-sys string that corresponds to the iteration specified,
    ///  will return a TreeData structure so that it can be passed to OGL
    ///
    /// needs a slightly different implementation for 3d

    TreeData interpret(int segType); //needs modification for 3d
};
#endif // TURTLE_H_

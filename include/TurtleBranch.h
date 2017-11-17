#ifndef TURTLEBRANCH_H_
#define TURTLEBRANCH_H_

#include <ngl/Vec4.h>
#include <ngl/Mat4.h>

///@file TurtleBranch.h
/// @brief Data structure used to store parameters to be push or popped when a branching symbol
/// is interpreted
///
struct TurtleBranch
{
  ///@brief index
  int index;
  ///@brief position
  ngl::Vec4 position;
  ///@brief rotationMatrix
  ngl::Mat4 rotationMatrix;
  ///@brief previousDirection
  ngl::Vec4 previousDirection;
  ///@brief drawStep
  float drawStep;
  ///@brief pRadius
  float pRadius;
  ///@brief colours
  ngl::Vec4 colour;
};

#endif // TURTLEBRANCH_H_

#ifndef TURTLENODES_H_
#define TURTLENODES_H_

#include <ngl/Vec4.h>

///@file TurtleNodes.h
/// @brief Data Structure to hold data of the nodes in order to generate a representable mesh
///
struct TurtleNodes
{
  ///@brief position
  ngl::Vec4 position;
  ///@brief previousDirection
  ngl::Vec4 previousDirection;
  ///@brief drawStep
  float drawStep;
  ///@brief pRadius
  float pRadius;
  ///@brief colour
  ngl::Vec4 colour;
  ///@brief closingBracket
  bool closingBracket;
};

#endif // TURTLENODES_H_

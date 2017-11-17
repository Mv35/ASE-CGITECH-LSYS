#ifndef TREEDATA_H
#define TREEDATA_H

#include <vector>
#include <ngl/Vec4.h>

///@file TreeData.h
/// @brief A data structure used to store geometric information (VAO)
///
struct TreeData
{
  ///@brief drawtype
  int drawType=1;
  ///@brief positions
  std::vector<ngl::Vec4> positions;
  ///@brief points
  std::vector<ngl::Vec4> points;
  ///@brief normals
  std::vector<ngl::Vec4> normals;
  ///@brief lineIndices
  std::vector<int> lineIndices;
  ///@brief indices
  std::vector<int> indices;
  ///@brief colours
  std::vector<ngl::Vec4> colours;
};
#endif // TREEDATA_H

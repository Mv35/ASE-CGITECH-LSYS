#ifndef OBJECTEXPORTER_H
#define OBJECTEXPORTER_H


#include <vector>
#include <iostream>
#include "ngl/Vec4.h"

///
/// @file ObjectExporter.h
/// \brief The ObjectExporter class is responsible for exporting
/// in .obj format.
/// @author Volpicelli Milo
///
class ObjectExporter
{
private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the array of vertices of the mesh
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<ngl::Vec4> m_vertices;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the array of indices of the mesh composing the faces (exports in triangles)
  std::vector<int> m_faces;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the normals of the vertices passed in (currently not implemented)
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<ngl::Vec4> m_normals;

public:
  //----------------------------------------------------------------------------------------------------------------------
  ///@brief Default constructor
  //----------------------------------------------------------------------------------------------------------------------
  ObjectExporter(){;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief verts and faces (only) constructor
  //----------------------------------------------------------------------------------------------------------------------
  ObjectExporter(std::vector<ngl::Vec4> vertices, std::vector<int> faces);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief constructor including normals
  //----------------------------------------------------------------------------------------------------------------------
  ObjectExporter(std::vector<ngl::Vec4> vertices, std::vector<int> faces, std::vector<ngl::Vec4> normals);

  //mutators
  //----------------------------------------------------------------------------------------------------------------------
  ///@brief vertices mutator
  /// @param vertices
  //----------------------------------------------------------------------------------------------------------------------
  void setVertices(std::vector<ngl::Vec4>);
  //----------------------------------------------------------------------------------------------------------------------
  ///@brief faces mutator
  /// @param faces
  //----------------------------------------------------------------------------------------------------------------------
  void setFaces(std::vector<int>);
  //----------------------------------------------------------------------------------------------------------------------
  ///@brief normals mutator
  /// @param normals
  //----------------------------------------------------------------------------------------------------------------------
  void setNormals(std::vector<ngl::Vec4>);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the export funtion taking as parameter the file path and name
  /// @param _fileName file name passed by reference
  //----------------------------------------------------------------------------------------------------------------------
  void saveObj( const std::string& fileName  ) const;


};



#endif // OBJECTEXPORTER_H

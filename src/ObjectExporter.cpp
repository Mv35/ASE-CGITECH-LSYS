#include <iostream>
#include <vector>
#include <fstream>
#include <boost/foreach.hpp>
#include "ngl/Vec4.h"
#include "ObjectExporter.h"


//vertices and faces constructor
ObjectExporter::ObjectExporter(std::vector<ngl::Vec4> vertices, std::vector<int> faces)
{
  m_vertices = vertices;
  //std::reverse(faces.begin(),faces.end());
  m_faces = faces;
}

//----------------------------------------------------------------------------------------------------------------

//full constructor
ObjectExporter::ObjectExporter(std::vector<ngl::Vec4> vertices, std::vector<int> faces, std::vector<ngl::Vec4> normals)
{

  //std::reverse(vertices.begin(),vertices.end());
  m_vertices = vertices;
  //std::reverse(faces.begin(),faces.end());
  m_faces = faces;
  m_normals = normals;
}

//------------------------------------------------------------------------------------------------


void ObjectExporter::setVertices(std::vector<ngl::Vec4> vertices)
{
    //std::reverse(vertices.begin(),vertices.end());
    m_vertices = vertices;
}

//------------------------------------------------------------------------------------------------

void ObjectExporter::setFaces(std::vector<int> faces)
{
  m_faces = faces;
}

//------------------------------------------------------------------------------------------------

void ObjectExporter::setNormals(std::vector<ngl::Vec4> normals)
{
  m_normals = normals;
}

//------------------------------------------------------------------------------------------------

//export funtion saving to the specified file
void ObjectExporter::saveObj( const std::string& fileName  ) const
{
    // Open the stream and parse
    std::fstream fileOut;
    fileOut.open(fileName.c_str(),std::ios::out);
    if (!fileOut.is_open())
    {
    std::cout <<"File : "<<fileName<<" Not found "<<'\n';
    return;
    }

    BOOST_FOREACH(ngl::Vec4 v , m_vertices)
    {
        fileOut<<"v "<<v.m_x<<" "<<v.m_y<<" "<<v.m_z<<'\n';
    }

    for(ngl::Vec4 v : m_vertices)
    {
        fileOut<<"v "<<v.m_x<<" "<<v.m_y<<" "<<v.m_z<<std::endl;
    }

    for(unsigned f=0; f<m_faces.size(); f+=3)
    {

      fileOut<<"f ";
      fileOut<<m_faces[f]+1<<' ';
      fileOut<<m_faces[f+1]+1<<' ';
      fileOut<<m_faces[f+2]+1<<' ';
      fileOut<<'\n';
    }



    BOOST_FOREACH(ngl::Vec4 v , m_normals)
    {
        fileOut<<"vn "<<v.m_x<<" "<<v.m_y<<" "<<v.m_z<<'\n';
    }


}
//----------------------------------------------------------------------------------------------------------------------

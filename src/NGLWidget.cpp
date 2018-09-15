#include "NGLWidget.h"

#include <ngl/Vec3.h>
#include <ngl/Light.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Material.h>
#include <ngl/ShaderLib.h>
#include <ngl/SimpleIndexVAO.h>

#include <iostream>
#include <sstream>


#include <QColorDialog>
#include <QtCore/QCoreApplication>
#include <QGuiApplication>
#include <QFileDialog>






NGLWidget::NGLWidget(QWidget *_parent) : QOpenGLWidget(_parent)
{
    setFocus();

    this->resize(_parent->size());

    m_lstype = 0;

    m_exportLSystemParameters = "";
    m_exportLSystemResults = "";



}

//----------------------------------------------------------------------------------------------------------------

NGLWidget::~NGLWidget(){}

void NGLWidget::initializeGL()
{
    ngl::NGLInit::instance();

    glClearColor(0.5f,0.5f,0.5f,1.0f);

    // enable depth testing for drawing
    glEnable(GL_DEPTH_TEST);
    // enable multisampling for smoother drawing
    glEnable(GL_MULTISAMPLE);
    //glEnable(GL_CCW);

    // Now we will create a basic Camera from the graphics library
    // This is a static camera so it only needs to be set once
    // First create Values for the camera position
    ngl::Vec3 from(0,4,8);
    ngl::Vec3 to(0,0,0);
    ngl::Vec3 up(0,1,0);
    m_cam.set(from,to,up);
    // set the shape using FOV 45 Aspect Ratio based on Width and Height
    // The final two are near and far clipping planes of 0.5 and 10
    m_cam.setShape(45.0f,720.0f/576.0f,0.05f,350.0f);

    ngl::ShaderLib *shader=ngl::ShaderLib::instance();

    shader->createShaderProgram("Phong");
    // now we are going to create empty shaders for Frag and Vert
    shader->attachShader("PhongVertex",ngl::ShaderType::VERTEX);
    shader->attachShader("PhongFragment",ngl::ShaderType::FRAGMENT);
    // attach the source
    shader->loadShaderSource("PhongVertex","shaders/PhongVertex.glsl");
    shader->loadShaderSource("PhongFragment","shaders/PhongFragment.glsl");
    // compile the shaders
    shader->compileShader("PhongVertex");
    shader->compileShader("PhongFragment");
    // add them to the program
    shader->attachShaderToProgram("Phong","PhongVertex");
    shader->attachShaderToProgram("Phong","PhongFragment");
    // now bind the shader attributes for most NGL primitives we use the following
    // layout attribute 0 is the vertex data (x,y,z)
    shader->bindAttribute("Phong",0,"inVert");
    // attribute 1 is the UV data u,v (if present)
    shader->bindAttribute("Phong",1,"inUV");
    // attribute 2 are the normals x,y,z
    shader->bindAttribute("Phong",2,"inNormal");

    // now we have associated this data we can link the shader
    shader->linkProgramObject("Phong");
    // and make it active ready to load values
    (*shader)["Phong"]->use();
    shader->setUniform("Normalize",1);
    shader->setUniform("viewerPos",m_cam.getEye().toVec3());
    // now pass the modelView and projection values to the shader
    // the shader will use the currently active material and light0 so set them
    ngl::Material m(ngl::STDMAT::POLISHEDSILVER);
    m.loadToShader("material");
    // we need to set a base colour as the material isn't being used for all the params
    shader->setUniform("Colour",0.23125f,0.23125f,0.23125f,1.0f);

    ngl::Light light(ngl::Vec3(2,2,2),ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1),ngl::LightModes::POINTLIGHT);
    // now create our light this is done after the camera so we can pass the
    // transpose of the projection matrix to the light to do correct eye space
    // transformations
    ngl::Mat4 iv=m_cam.getViewMatrix();
    iv.transpose();
    light.setTransform(iv);
    light.setAttenuation(1,0,0);
    light.enable();
    // load these values to the shader as well
    light.loadToShader("light");

    constructVAO();

    m_text.reset (new ngl::Text(QFont("Arial", 18)));
    m_text->setScreenSize(this->size().width(), this->size().height());
    m_text->setColour(1.0,1.0,0.0);
    update();
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::resizeGL(int _w, int _h)
{

    m_cam.setShape( 45.0f, static_cast<float>( _w ) / _h, 0.05f, 350.0f );
    m_win.width  = static_cast<int>( _w * devicePixelRatio() );
    m_win.height = static_cast<int>( _h * devicePixelRatio() );
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::loadMatricesToShader()
{


   ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)["Phong"]->use();


    ngl::Mat4 MV;

    ngl::Mat3 normalMatrix;
    ngl::Mat4 M;
    M=m_transform.getMatrix();
    MV=m_cam.getViewMatrix()*M;

    normalMatrix=MV;
    normalMatrix.inverse();
    shader->setUniform("MV",MV);

    shader->setUniform("normalMatrix",normalMatrix);
    shader->setUniform("M",M);
    ngl::Mat4 MVP=m_cam.getVPMatrix() *
                  m_mouseGlobalTX*
                  m_transform.getMatrix();

    shader->setUniform("MVP",MVP);


}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,m_win.width,m_win.height);

    ngl::Mat4 rotX;
    ngl::Mat4 rotY;
    // create the rotation matrices
    rotX.rotateX(m_win.spinXFace);
    rotY.rotateY(m_win.spinYFace);
    // multiply the rotations
    m_mouseGlobalTX=rotY*rotX;
    // add the translations
    m_mouseGlobalTX.m_m[3][0] = m_modelPos.m_x;
    m_mouseGlobalTX.m_m[3][1] = m_modelPos.m_y;
    m_mouseGlobalTX.m_m[3][2] = m_modelPos.m_z;



    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)["Phong"]->use();

    m_transform.reset();

    //Load the matrices
    loadMatricesToShader();

    if(m_wireframe == true)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_treeVao->bind();

    m_treeVao->draw();

    m_treeVao->unbind();
    m_treeVao->numIndices();

    drawMeshinfo();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::constructVAO()
{
    m_treeVao.reset(ngl::VAOFactory::createVAO(ngl::simpleIndexVAO,GL_TRIANGLES));
    m_treeVao->bind();

    glPointSize(4);

    m_treeVao->setData( ngl::SimpleIndexVAO::VertexData(m_tree.m_points.size()*sizeof(ngl::Vec4),m_tree.m_points[0].m_x,m_tree.m_indices.size(),&m_tree.m_indices[0],GL_UNSIGNED_INT,GL_STATIC_DRAW));
    m_treeVao->setVertexAttributePointer(0,4,GL_FLOAT,0,0);
    m_treeVao->setData(ngl::SimpleIndexVAO::VertexData(m_tree.m_colours.size()*sizeof(ngl::Vec4),m_tree.m_colours[0].m_x,m_tree.m_indices.size(),&m_tree.m_indices[0],GL_UNSIGNED_INT,GL_STATIC_DRAW));
    m_treeVao->setVertexAttributePointer(1,4,GL_FLOAT,0,0);
    m_treeVao->setNumIndices(m_tree.m_indices.size());

    m_treeVao->setData(ngl::SimpleIndexVAO::VertexData(m_tree.m_normals.size()*sizeof(ngl::Vec4),m_tree.m_normals[0].m_x,m_tree.m_indices.size(),&m_tree.m_indices[0],GL_UNSIGNED_INT,GL_STATIC_DRAW));
    m_treeVao->setVertexAttributePointer(2,4,GL_FLOAT,0,0);

    m_treeVao->unbind();
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::setMesh(TreeData tree)
{
    m_tree = tree;
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::toggleWireframe()
{
    m_wireframe^=true;

    update();
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::toggleMeshinfo(bool _mode)
{
  m_meshinfo = _mode;
  update();
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::drawMeshinfo()
{

    if(m_meshinfo)
    {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

        QString text=QString("Vertices: %1").arg(m_tree.m_points.size());
        m_text->renderText(10,18,text);

    }



}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::toggleWireframe(bool _mode	 )
{
  m_wireframe =_mode;

  update();
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::exportObj()
{
    //getting the file path from the user
    QString filePath = QFileDialog::getSaveFileName(this,tr("Save OBJ file"),"/home",tr("Waveform OBJ Files(*.obj)"));
    std::cout<<"called export"<<'\n';
    //creating an obj exporter and saving the file to the user specified destination

    ObjectExporter myObj(m_tree.m_points,m_tree.m_indices,m_tree.m_normals);
    myObj.saveObj(filePath.toLocal8Bit().constData());
}

//----------------------------------------------------------------------------------------------------------------


void NGLWidget::getFile()
{
  // Storing the path to the file chosen by the user with a File Dialog
  QString txt_file = QFileDialog::getOpenFileName(this,tr("Find L-system"),"/home",tr("Text Files(*.txt)"));

  // Calling the parse from file function passing the user chosen file
  parseLSystemFromFile(txt_file);
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::parseLSystemFromFile(QString _file_name)
{
  // Converting QString to a const char*
  QByteArray ba_file_name = _file_name.toLocal8Bit();
  const char *c_file_name = ba_file_name.data();

  // Creating a file parser and a parameters structure
  LSysParser parser;
  LSysStruct parameters;
  LSysStructForFile ui_parameters;
  parser.toParse(c_file_name, parameters, ui_parameters);  //fix the pass by ref

  m_lParameters = parameters;
  m_uiParameters = ui_parameters;


  drawLSystem();
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::parseLSystemFromUI()
{
  // Creating a file parser and a parameters structure
  LSysParser parser;
  LSysStruct parameters;
  LSysStructForFile ui_parameters;
  parser.toParse("tmp/currentSystem.txt", parameters, ui_parameters);

  m_lParameters = parameters;
  m_uiParameters = ui_parameters;

  if(m_instantChanges)
    drawLSystem();
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::constructLSystem()
{
    LSysExtFactory::registerLSys("S2L",LSys2L::generate);
    LSys*S2L = LSysExtFactory::generateLSys("S2L",m_lParameters);
    S2L->develop(m_lParameters.m_iteration,m_results,true);

    if(m_exportLSystemParameters[0] != '\0')
    {
        S2L->Tofile(m_exportLSystemParameters);
        m_exportLSystemParameters = "";
    }
    delete S2L;
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::drawLSystem()
{



    //if(m_drawRadius < 0.01)
    if((!m_radiusChanged)||(m_drawRadius < 0.01))
    {
      m_drawRadius = 0.03f;
      m_radiusChanged = false;
    }
    //if(m_divisions< 2)
    if((m_divisions< 2))
    {
        m_divisions = 8;
        m_divisionsChanged = false;
    }


    TreeData m_currentTree;


    LSysExtFactory::registerLSys("S2L",LSys2L::generate);
    LSys*S2L = LSysExtFactory::generateLSys("S2L",m_lParameters);
    S2L->develop(m_lParameters.m_iteration,m_results,true);
    //S2L->print();



    //S2L->Tofile("prova4.txt");
    delete S2L;

    TurtleParameters turtle_params;
    std::string dictionary[] = {"+", "-", "^", "&", "/", "<", ">", ",", "[", "]", "C", "!", "~"};
    turtle_params.m_dictSymbols.insert(turtle_params.m_dictSymbols.begin(), dictionary,dictionary+(sizeof(dictionary)/sizeof(dictionary[0])));
    turtle_params.m_constants= m_lParameters.m_constants;
    turtle_params.m_lSys = m_results;
    turtle_params.m_iteration = m_results.size()-1;
    turtle_params.m_angle = m_lParameters.m_angle;
    turtle_params.m_drawLenght = m_lParameters.m_drawLenght;

    Turtle turtle(turtle_params);

    m_currentTree = turtle.interpret(m_drawRadius, m_divisions);
    m_tree = m_currentTree;
    m_tree.drawType=1;

    initializeGL();
    update();
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::toggleInstantChanges(bool mode)
{
  m_instantChanges = mode;
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::changeRadius(int rad)
{
  m_radiusChanged = true;

  m_drawRadius = (double)rad/1000.0;

  if(m_instantChanges)
    drawLSystem();
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::changeDetail(int detail)
{
  m_divisions = detail;
  m_divisionsChanged = true;

  if(m_instantChanges)
    drawLSystem();
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::changeIterations(int iters)
{
  m_lParameters.m_iteration = iters;

  if(m_instantChanges)
    drawLSystem();
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::changeAngle(int angle)
{
  m_lParameters.m_angle = angle;

  if(m_instantChanges)
    drawLSystem();
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::changeScale(double scale)
{
  m_lParameters.m_drawLenght =  scale;

  if(m_instantChanges)
    drawLSystem();
}

//----------------------------------------------------------------------------------------------------------------

LSysStructForFile NGLWidget::getLSysStructForFile()
{
    return m_uiParameters;
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::exportLSystemParameters()
{
  //getting the file path from the user
  QString filePath = QFileDialog::getSaveFileName(this,tr("Save txt file"),"/home",tr("Plain Text Files(*.txt)"));

  //converting QString to const char*
  QByteArray byteArray = filePath.toUtf8();
  m_exportLSystemParameters = byteArray.constData();

  //that the export function can be called
  constructLSystem();
}

//----------------------------------------------------------------------------------------------------------------

void NGLWidget::exportLSystemResult()
{
  //getting the file path from the user
  QString filePath = QFileDialog::getSaveFileName(this,tr("Save txt file"),"/home",tr("Plain Text Files(*.txt)"));

  //converting QString to const char*
  QByteArray byteArray = filePath.toUtf8();
  m_exportLSystemResults = byteArray.constData();

  if(m_exportLSystemResults[0] != '\0')
  {
    std::ofstream myFile;
    myFile.open(m_exportLSystemResults);
    myFile << m_results[m_results.size()-1] << std::endl;
    myFile.close();
    m_exportLSystemParameters = "";
  }
}

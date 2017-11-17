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


}

NGLWidget::~NGLWidget(){}

void NGLWidget::initializeGL()
{
    ngl::NGLInit::instance();

    glClearColor(0.8f,0.8f,0.8f,1.0f);

    glEnable((GL_DEPTH_TEST));
    //glEnable(GL_MULTISAMPLE);

    //m_currentDmode = GL_LINES;

    ngl::Vec3 eye(0,1,4);
    ngl::Vec3 look(0,20,0);
    ngl::Vec3 up(0,1,0);

    m_camera = new ngl::Camera(eye,look,up);

    m_camera->setShape(45,float(1024/720),0.0001,300);

    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    shader->setUniform("Colour",1.0f,1.0f,1.0f,1.0f);

    //m_light = new ngl::Light(ngl::Vec3(10,7,0),ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1),ngl::LightModes::DIRECTIONALLIGHT);

    ngl::Mat4 iv=m_camera->getViewMatrix();
    iv.transpose();
    //m_light->setTransform(iv);
    //m_light->setAttenuation(1,0,0);
    //m_light->enable();

    //m_light->loadToShader("light");

    /// Initializing Colour Shader
    shader->createShaderProgram("ColourShader");
    shader->attachShader("ColourVertex",ngl::ShaderType::VERTEX);
    shader->attachShader("ColourFragment",ngl::ShaderType::FRAGMENT);

    shader->loadShaderSource("ColourVertex","shaders/ColourVertex.glsl");
    shader->loadShaderSource("ColourFragment","shaders/ColourFragment.glsl");

    shader->compileShader("ColourVertex");
    shader->compileShader("ColourFragment");

    shader->attachShaderToProgram("ColourShader","ColourVertex");
    shader->attachShaderToProgram("ColourShader","ColourFragment");

    shader->linkProgramObject("ColourShader");

    (*shader)["nglColourShader"]->use();


    LSysStruct tr;
    LSysStruct trparsed;
    LSysStructForFile tp;
    //LSysParser::toParse("prova.txt",tr,tp);

    std::vector<std::string> sp;

    //so->develop(5,sp,true);

    //si->print();

    //std::cout<<"aaaaaaa"<<"\n";
    //so->Tofile("prova.txt");
    LSysParser parser;

    //parser.toParse("prova.txt", tr);
    TreeData m_currentTree;
    parser.toParse("prova3.txt",trparsed,tp);
    LSysExtFactory::registerLSys("S0L",LSys0L::generate);
    LSys*S0L = LSysExtFactory::generateLSys("S0L",trparsed);
    //std::cout<<trparsed.Prules[1].pre_condition<<trparsed.Prules[1].post_condition<<'\n';
    //std::cout<<trparsed.Prules[0].key<<'\n';
    S0L->Tofile("prova4.txt");
    S0L->print();
    S0L->develop(trparsed.iteration,sp,true);
    std::cout<<sp[0]<<'\n';
    std::cout<<sp[2]<<'\n';
    TurtleParameters turtle_params;
    std::string dictionary[] = {"+", "-", "^", "&", "/", "<", ">", ",", "[", "]", "C", "!", "~"};
    turtle_params.dictSymbols.insert(turtle_params.dictSymbols.begin(), dictionary,dictionary+(sizeof(dictionary)/sizeof(dictionary[0])));
    turtle_params.constants= trparsed.constants;
    turtle_params.lSys = sp;
    turtle_params.iteration = sp.size()-1;
    turtle_params.angle = trparsed.angle;
    turtle_params.drawLenght = trparsed.drawLenght;

    Turtle turtle(turtle_params);

    m_currentTree = turtle.interpret(1);
    m_tree = m_currentTree;
    m_tree.drawType=1;
    constructVAO();
    //for(unsigned int i=0; i<m_tree.points.size();++i)
        //std::cout<<m_tree.points[i].m_x<<'\n';


    //ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    //prim->

    update();
}

void NGLWidget::resizeGL(int _width, int _height)
{
    _w= _width*devicePixelRatio();
    _h= _height*devicePixelRatio();
    //glViewport(0,0,_w,_h);
    m_camera->setShape(45,float(_w/_h),10,300);
}

void NGLWidget::loadMatricesToShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)["ColourShader"]->use();

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;

  M= m_transformation.getMatrix();
  MV= m_transformation.getMatrix()*m_camera->getViewMatrix();
  MVP=MV*m_camera->getProjectionMatrix() ;
  normalMatrix=m_mstack.MV().inverse().transpose();


  shader->setUniform("MV",MV);
  shader->setUniform("MVP",m_mstack.MVP());
  shader->setUniform("normalMatrix",normalMatrix);
  shader->setUniform("M",M);
}
void NGLWidget::paintGL()
{
    glViewport(0,0,_w/2,_h/2);
    glViewport(0,0,_w,_h);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)["ColourShader"]->use();

    //ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();

    ngl::Transformation trans;
    ngl::Mat4 xRot;
    ngl::Mat4 yRot;

    //xRot.rotateX(m_spinXFace);
    //yRot.rotateY(m_spinYFace);

    ngl::Mat4 final=yRot*xRot;

    //final.m_m[3][0] = m_modelPos.m_x;
    //final.m_m[3][1] = m_modelPos.m_y;
    //final.m_m[3][2] = m_modelPos.m_z;


    trans.setMatrix(final);

    trans.loadGlobalAndCurrentMatrixToShader("trans", trans,ngl::ActiveMatrix::NORMAL);

    ngl::Mat4 iv = m_camera->getViewMatrix();

    iv.transpose();
    //m_light->setTransform(iv);
    // load these values to the shader as well
    //m_light->loadToShader("light");

    //Load the matrices
    loadMatricesToShader();

    m_treeVao->bind();
    m_treeVao->draw();
    m_treeVao->unbind();
    m_treeVao->numIndices();

    //prim->draw("teapot");
}

void NGLWidget::constructVAO()
{
    m_treeVao.reset(ngl::VAOFactory::createVAO(ngl::simpleIndexVAO,GL_LINES));
    m_treeVao->bind();

    glPointSize(4);

    m_treeVao->setData( ngl::SimpleIndexVAO::VertexData(m_tree.points.size()*sizeof(ngl::Vec4),m_tree.points[0].m_x,m_tree.indices.size(),&m_tree.indices[0],GL_UNSIGNED_INT,GL_STATIC_DRAW));
    m_treeVao->setVertexAttributePointer(0,4,GL_FLOAT,0,0);
    m_treeVao->setData(ngl::SimpleIndexVAO::VertexData(m_tree.colours.size()*sizeof(ngl::Vec4),m_tree.colours[0].m_x,m_tree.indices.size(),&m_tree.indices[0],GL_UNSIGNED_INT,GL_STATIC_DRAW));
    m_treeVao->setVertexAttributePointer(1,4,GL_FLOAT,0,0);
    m_treeVao->setNumIndices(m_tree.indices.size());

    m_treeVao->setData(ngl::SimpleIndexVAO::VertexData(m_tree.normals.size()*sizeof(ngl::Vec4),m_tree.normals[0].m_x,m_tree.indices.size(),&m_tree.indices[0],GL_UNSIGNED_INT,GL_STATIC_DRAW));
    m_treeVao->setVertexAttributePointer(2,4,GL_FLOAT,0,0);

    m_treeVao->unbind();
}



#ifndef NGLWIDGET_H_
#define NGLWIDGET_H_

#include <ngl/Camera.h>
#include <ngl/Vec3.h>
#include <ngl/Colour.h>
#include <ngl/Light.h>
#include <ngl/Text.h>
#include <MatrixStack.h>

#include <QEvent>
#include <QResizeEvent>
#include <QGLWidget>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QOpenGLWidget>

#include "LSysStruct.h"
#include "LSysStructForFile.h"
#include "LSysExtFactory.h"
#include "Turtle.h"
#include "TurtleParameters.h"
#include "LSys.h"
#include "LSys0L.h"
#include "LSysParser.h"
#include "TreeData.h"

///@file NGLWidget.h
///@brief GLWidget class derived from qt's QGLWidget class
///
///
class NGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    //constructor and deconstructor
    NGLWidget(QWidget *_parent);
    ~NGLWidget();

private:

    ///@brief method to load matrices onto used shader

    void loadMatricesToShader();

    ///@brief data structure used to store l-system parameters
    //LSysStruct m_lSysParam;

    //LSysStructForFile m_lSysParamFF;

    //const char * my_file;

    ///@brief vector of strings to hold the various iterations of the developed l-system
    //std::vector<std::string> m_devResults;

    //int m_spinXFace;

    //int m_spinYFace;

    //ngl::Vec3 m_modelPos;

    TreeData m_currentTree;

    int m_lstype;

    GLenum m_developedlSys;

    void constructVAO();

    TreeData m_tree;

    int _w;

    int _h;

    std::unique_ptr<ngl::AbstractVAO> m_treeVao;

    //GLenum m_drawtype;

    //ngl::Light* m_light;
    //std::unique_ptr<ngl::Light> m_light;
protected:

    void initializeGL() override;

    void resizeGL(const int _w, const int _y) override;

    void paintGL() override;

    //std::unique_ptr<ngl::Camera> m_camera;
    ngl::Camera * m_camera;
    ngl::Transformation m_transformation;

    MatrixStack m_mstack;



};
#endif //NGLWIDGET_H_

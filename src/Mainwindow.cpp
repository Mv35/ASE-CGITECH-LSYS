#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);
  // create an openGL format and pass to the new GLWidget
  QGLFormat format;
  format.setVersion(4,2);
  format.setProfile( QGLFormat::CoreProfile);

  m_gl = new NGLWidget(this);

  // Creating the main render window
  m_ui->gridLayout->addWidget(m_gl,0,0,2,1);
  this->setWindowTitle("L-Systems");
  //----------------------------------------------------------------------------------------------------------------------
  //Wireframe
  connect(m_ui->m_wireframeCheckBox,SIGNAL(toggled(bool)),m_gl,SLOT(toggleWireframe(bool)));
  //----------------------------------------------------------------------------------------------------------------------
  //Mesh Vertices Count
  connect(m_ui->m_meshInfoCheckBox,SIGNAL(toggled(bool)),m_gl,SLOT(toggleMeshinfo(bool)));
  //----------------------------------------------------------------------------------------------------------------------
  //Export .obj
  connect(m_ui->m_exportObjButton,SIGNAL(clicked()),m_gl,SLOT(exportObj()));
  //----------------------------------------------------------------------------------------------------------------------
  //Export LSys Parameters
  connect(m_ui->m_expParamButton,SIGNAL(clicked()),m_gl,SLOT(exportLSystemParameters()));
  //----------------------------------------------------------------------------------------------------------------------
  //Export LSys
  connect(m_ui->m_expLsysButton,SIGNAL(clicked()),m_gl,SLOT(exportLSystemResult()));
  //----------------------------------------------------------------------------------------------------------------------
  //Instant Changes Mode
  connect(m_ui->m_toggleInstantCheckBox,SIGNAL(toggled(bool)),m_gl,SLOT(toggleInstantChanges(bool)));
  //----------------------------------------------------------------------------------------------------------------------
  //Detail, Geometry Subdivisions
  connect(m_ui->m_detailLvlBox,SIGNAL(valueChanged(int)),m_gl,SLOT(changeDetail(int)));
  //----------------------------------------------------------------------------------------------------------------------
  //Radius
  connect(m_ui->m_radiusSlider,SIGNAL(valueChanged(int)),m_gl,SLOT(changeRadius(int)));
  //----------------------------------------------------------------------------------------------------------------------
  //File input
  connect(m_ui->m_filePathButton,SIGNAL(clicked()),m_gl,SLOT(getFile()));
  connect(m_ui->m_filePathButton,SIGNAL(clicked()),this,SLOT(getLParametersFromSystem()));
  //----------------------------------------------------------------------------------------------------------------------
  //Build Button
  connect(m_ui->m_buildButton,SIGNAL(clicked()),this,SLOT(saveParametersToFile()));
  connect(m_ui->m_buildButton,SIGNAL(clicked()),m_gl,SLOT(parseLSystemFromUI()));
  connect(m_ui->m_buildButton,SIGNAL(clicked()),m_gl,SLOT(drawLSystem()));

  //----------------------------------------------------------------------------------------------------------------------

  ///Parameters
  //----------------------------------------------------------------------------------------------------------------------
  // iterations
  connect(m_ui->m_iterationsBox,SIGNAL(valueChanged(int)),m_gl,SLOT(changeIterations(int)));
  //----------------------------------------------------------------------------------------------------------------------
  // angle
  connect(m_ui->m_angleBox,SIGNAL(valueChanged(int)),m_gl,SLOT(changeAngle(int)));
  //----------------------------------------------------------------------------------------------------------------------
  // scale
  connect(m_ui->m_scaleBox,SIGNAL(valueChanged(double)),m_gl,SLOT(changeScale(double)));
  //----------------------------------------------------------------------------------------------------------------------
  // constants
  connect(m_ui->m_constantsBox,SIGNAL(editingFinished()),this,SLOT(saveParametersToFile()));
  connect(m_ui->m_constantsBox,SIGNAL(editingFinished()),m_gl,SLOT(parseLSystemFromUI()));
  //----------------------------------------------------------------------------------------------------------------------
  // axiom
  connect(m_ui->m_axiomBox,SIGNAL(editingFinished()),this,SLOT(saveParametersToFile()));
  connect(m_ui->m_axiomBox,SIGNAL(editingFinished()),m_gl,SLOT(parseLSystemFromUI()));
  //----------------------------------------------------------------------------------------------------------------------
  //rule1
  connect(m_ui->m_rule1Box,SIGNAL(editingFinished()),this,SLOT(saveParametersToFile()));
  connect(m_ui->m_rule1Box,SIGNAL(editingFinished()),m_gl,SLOT(parseLSystemFromUI()));
  //----------------------------------------------------------------------------------------------------------------------
  //rule2
  connect(m_ui->m_rule2Box,SIGNAL(editingFinished()),this,SLOT(saveParametersToFile()));
  connect(m_ui->m_rule2Box,SIGNAL(editingFinished()),m_gl,SLOT(parseLSystemFromUI()));
  //----------------------------------------------------------------------------------------------------------------------
  //rule3
  connect(m_ui->m_rule3Box,SIGNAL(editingFinished()),this,SLOT(saveParametersToFile()));
  connect(m_ui->m_rule3Box,SIGNAL(editingFinished()),m_gl,SLOT(parseLSystemFromUI()));
  //----------------------------------------------------------------------------------------------------------------------
  //rule4
  connect(m_ui->m_rule4Box,SIGNAL(editingFinished()),this,SLOT(saveParametersToFile()));
  connect(m_ui->m_rule4Box,SIGNAL(editingFinished()),m_gl,SLOT(parseLSystemFromUI()));
  //----------------------------------------------------------------------------------------------------------------------
  //rule5
  connect(m_ui->m_rule5Box,SIGNAL(editingFinished()),this,SLOT(saveParametersToFile()));
  connect(m_ui->m_rule5Box,SIGNAL(editingFinished()),m_gl,SLOT(parseLSystemFromUI()));
  //----------------------------------------------------------------------------------------------------------------------
}

//----------------------------------------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
  //delete m_ui;
}

//----------------------------------------------------------------------------------------------------------------

void MainWindow::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  // turn on wirframe rendering
  case Qt::Key_W : m_gl->toggleWireframe(); break;
  // turn off wire frame
  //case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
  // show full screen
  case Qt::Key_F : showFullScreen(); break;
  // show windowed
  case Qt::Key_N : showNormal(); break;
  //default
  default : break;
  }
  // finally update the GLWindow and re-draw
  update();
}

//----------------------------------------------------------------------------------------------------------------

void MainWindow::getLParametersFromSystem()
{
  LSysStructForFile params = m_gl->getLSysStructForFile();

  // Getting the iterations
  m_ui->m_iterationsBox->setValue(params.m_iteration);

  // Getting the angle
  m_ui->m_angleBox->setValue(params.m_angle);

  // Getting the segment size
  m_ui->m_scaleBox->setValue(params.m_drawLenght);

  // Getting the constants
  std::string consts;
  for(unsigned i=0; i<params.m_constants.size(); ++i)
  {
    consts += params.m_constants[i] + " ";
  }
  if(consts == "")
    consts = "---";
  m_ui->m_constantsBox->setText(QString::fromStdString(consts));

  // Getting the axiom
  QString axiomQStr = QString::fromStdString(params.m_axiom);
  m_ui->m_axiomBox->setText(axiomQStr);

  // Getting the rules
  params.m_Prules.resize(5);
  m_ui->m_rule1Box->setText(QString::fromStdString(params.m_Prules[0]));
  m_ui->m_rule2Box->setText(QString::fromStdString(params.m_Prules[1]));
  m_ui->m_rule3Box->setText(QString::fromStdString(params.m_Prules[2]));
  m_ui->m_rule4Box->setText(QString::fromStdString(params.m_Prules[3]));
  m_ui->m_rule5Box->setText(QString::fromStdString(params.m_Prules[4]));
}

//----------------------------------------------------------------------------------------------------------------

void MainWindow::saveParametersToFile()
{
  //creating a temporary file to which the current rules are written and read from
  const char* tmpFile = "tmp/currentSystem.txt";
  std::ofstream myFile;
  QByteArray tmpByteArray;

  // Writing the current systems parameters to the file
  myFile.open(tmpFile);
  // iterations
  myFile << "iterations:" << '\n';
  myFile << m_ui->m_iterationsBox->value() << " ;" <<'\n';
  myFile << '\n';

  // angle
  myFile << "angle:" << '\n';
  myFile << m_ui->m_angleBox->value() << " ;" << '\n';
  myFile << '\n';

  // scale
  myFile << "scale:" << '\n';
  myFile << m_ui->m_scaleBox->value() << " ;" << '\n';
  myFile << '\n';

  // constants
  if(m_ui->m_constantsBox->text() != "---")
  {
    myFile << "constants:" << '\n';
    tmpByteArray = m_ui->m_constantsBox->text().toUtf8();
    const char* cConstants = tmpByteArray.constData();
    myFile << cConstants << " ;" << '\n';
    myFile << '\n';
  }

  // axiom
  myFile << "axiom:" << '\n';
  tmpByteArray = m_ui->m_axiomBox->text().toUtf8();
  const char* cAxiom = tmpByteArray.constData();
  myFile << cAxiom << " ;" << '\n';
  myFile << '\n';

  // rules
  myFile << "Prules:" << '\n';

  tmpByteArray = m_ui->m_rule1Box->text().toUtf8();
  const char* cRule = tmpByteArray.constData();
  myFile << cRule << '\n';

  tmpByteArray = m_ui->m_rule2Box->text().toUtf8();
  cRule = tmpByteArray.constData();
  myFile << cRule << '\n';

  tmpByteArray = m_ui->m_rule3Box->text().toUtf8();
  cRule = tmpByteArray.constData();
  myFile << cRule << '\n';

  tmpByteArray = m_ui->m_rule4Box->text().toUtf8();
  cRule = tmpByteArray.constData();
  myFile << cRule << '\n';

  tmpByteArray = m_ui->m_rule5Box->text().toUtf8();
  cRule = tmpByteArray.constData();
  myFile << cRule << '\n';

  myFile << '\n';

  myFile.close();
}
//----------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <QApplication>
#include "MainWindow.h"
#include "LSys.h"
#include "LSys0L.h"
#include "LSysExtFactory.h"
#include "LSysParser.h"
#include "LSysStructForFile.h"
#include "Turtle.h"
#include <QSurfaceFormat>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QSurfaceFormat format;
  format.setMajorVersion(4);
  format.setMinorVersion(1);
  format.setProfile(QSurfaceFormat::OpenGLContextProfile::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  MainWindow w;

/*

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
  LSysExtFactory::registerLSys("S0L",LSys0L::generate);
  LSys*temp = LSysExtFactory::generateLSys("S0L",tr);
  temp->Tofile("prova.txt");
  //parser.toParse("prova.txt", tr);
  TreeData m_currentTree;
  parser.toParse("prova3.txt",trparsed,tp);
  LSysExtFactory::registerLSys("S0L",LSys0L::generate);
  LSys*S0L = LSysExtFactory::generateLSys("S0L",trparsed);
  //std::cout<<trparsed.Prules[1].pre_condition<<trparsed.Prules[1].post_condition<<'\n';
  //std::cout<<trparsed.Prules[0].key<<'\n';
  S0L->Tofile("prova4.txt");
  //S0L->print();
  S0L->develop(trparsed.iteration,sp,true);
  std::cout<<sp[0]<<'\n';
  std::cout<<sp[2]<<'\n';
  TurtleParameters turtle_params;
  std::string dictionary[] = {"+", "-", "^", "&", "/", "<", ">", ",", "[", "]", "C", "!", "~"};
  turtle_params.dictSymbols.insert(turtle_params.dictSymbols.begin(), dictionary,dictionary+(sizeof(dictionary)/sizeof(dictionary[0])));
  turtle_params.constants= tp.constants;
  turtle_params.lSys = sp;
  turtle_params.iteration = sp.size()-1;
  turtle_params.angle = tp.angle;
  turtle_params.drawLenght = tp.drawLenght;

  Turtle turtle(turtle_params);

  m_currentTree = turtle.interpret(1);
  for(unsigned int i=0;i<m_currentTree.points.size();++i)
    {
       //std::cout<<m_currentTree.points[i].m_x<<'\n';
       std::cout<<m_currentTree.lineIndices[i]<<'\n';
    }
       //for(std::vector<std::string>::iterator iter = results.begin();iter!=results.end();++iter)
      //std::cout<<*iter<<"\n";

    */
  w.show();
  return app.exec();
}




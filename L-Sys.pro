######################################################################
# Automatically generated by qmake (3.1) Mon Nov 6 14:24:22 2017
######################################################################

# This specifies the exe name
TARGET=L-Sys
# where to put the .o files
OBJECTS_DIR=obj
# core Qt Libs to use add more here if needed.
QT+=gui opengl core
# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
        cache()
        DEFINES +=QT5BUILD
}

# were are going to default to a console app
CONFIG += console

#INCLUDEPATH+=include
HEADERS += include/LSys.h include/LSysExtFactory.h include/LSysStruct.h include/ProductionRule.h \
    include/LSys0L.h \
    include/TreeData.h \
    include/LSysStructForFile.h \
    include/LSysParser.h \
    include/TurtleParameters.h \
    include/Turtle.h \
    include/TurtleNodes.h \
    include/TurtleBranch.h \
    include/NGLWidget.h \
    include/MainWindow.h \
    include/MatrixStack.h

SOURCES += src/LSys.cpp src/LSysExtFactory.cpp src/main.cpp \
    src/LSys0L.cpp \
    src/LSysParser.cpp \
    src/Turtle.cpp \
    src/NGLWidget.cpp \
    src/MainWindow.cpp \
    src/MatrixStack.cpp


OTHER_FILES+= shaders/ColourFragment.glsl \
              shaders/ColourVertex.glsl

FORMS += ui/MainWindow.ui \


MOC_DIR=moc
#INCLUDEPATH += include
UI_DIR= include
UI_HEADERS_DIR= include
NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){ # note brace must be here
        message("including $HOME/NGL")
        include($(HOME)/NGL/UseNGL.pri)
}
else{ # note brace must be here
        message("Using custom NGL location")
        include($(NGLDIR)/UseNGL.pri)
}



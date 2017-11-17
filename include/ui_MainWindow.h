/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *m_centralWidget;
    QGridLayout *m_gridLayout;
    QGridLayout *gridLayout;
    QMenuBar *m_menuBar;
    QToolBar *m_mainToolBar;
    QStatusBar *m_statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        m_centralWidget = new QWidget(MainWindow);
        m_centralWidget->setObjectName(QStringLiteral("m_centralWidget"));
        m_gridLayout = new QGridLayout(m_centralWidget);
        m_gridLayout->setSpacing(6);
        m_gridLayout->setContentsMargins(11, 11, 11, 11);
        m_gridLayout->setObjectName(QStringLiteral("m_gridLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        m_gridLayout->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(m_centralWidget);
        m_menuBar = new QMenuBar(MainWindow);
        m_menuBar->setObjectName(QStringLiteral("m_menuBar"));
        m_menuBar->setGeometry(QRect(0, 0, 400, 22));
        MainWindow->setMenuBar(m_menuBar);
        m_mainToolBar = new QToolBar(MainWindow);
        m_mainToolBar->setObjectName(QStringLiteral("m_mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, m_mainToolBar);
        m_statusBar = new QStatusBar(MainWindow);
        m_statusBar->setObjectName(QStringLiteral("m_statusBar"));
        MainWindow->setStatusBar(m_statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

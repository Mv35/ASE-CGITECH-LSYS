/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *m_centralWidget;
    QGridLayout *gridLayout;
    QCheckBox *m_toggleInstantCheckBox;
    QTabWidget *tabWidget;
    QWidget *Parameters;
    QSpinBox *m_angleBox;
    QDoubleSpinBox *m_scaleBox;
    QSpinBox *m_iterationsBox;
    QLineEdit *m_axiomBox;
    QLineEdit *m_constantsBox;
    QLineEdit *m_rule1Box;
    QLineEdit *m_rule2Box;
    QLineEdit *m_rule3Box;
    QLineEdit *m_rule4Box;
    QLineEdit *m_rule5Box;
    QSlider *m_radiusSlider;
    QSpinBox *m_detailLvlBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QWidget *Exports;
    QPushButton *m_expLsysButton;
    QPushButton *m_expParamButton;
    QPushButton *m_exportObjButton;
    QPushButton *m_filePathButton;
    QPushButton *m_buildButton;
    QCheckBox *m_wireframeCheckBox;
    QCheckBox *m_meshInfoCheckBox;
    QMenuBar *m_menuBar;
    QToolBar *m_mainToolBar;
    QStatusBar *m_statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(857, 708);
        m_centralWidget = new QWidget(MainWindow);
        m_centralWidget->setObjectName(QStringLiteral("m_centralWidget"));
        gridLayout = new QGridLayout(m_centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_toggleInstantCheckBox = new QCheckBox(m_centralWidget);
        m_toggleInstantCheckBox->setObjectName(QStringLiteral("m_toggleInstantCheckBox"));
        m_toggleInstantCheckBox->setChecked(false);

        gridLayout->addWidget(m_toggleInstantCheckBox, 2, 2, 1, 1);

        tabWidget = new QTabWidget(m_centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setMaximumSize(QSize(210, 500));
        Parameters = new QWidget();
        Parameters->setObjectName(QStringLiteral("Parameters"));
        m_angleBox = new QSpinBox(Parameters);
        m_angleBox->setObjectName(QStringLiteral("m_angleBox"));
        m_angleBox->setGeometry(QRect(140, 130, 48, 25));
        m_scaleBox = new QDoubleSpinBox(Parameters);
        m_scaleBox->setObjectName(QStringLiteral("m_scaleBox"));
        m_scaleBox->setGeometry(QRect(120, 160, 68, 25));
        m_iterationsBox = new QSpinBox(Parameters);
        m_iterationsBox->setObjectName(QStringLiteral("m_iterationsBox"));
        m_iterationsBox->setGeometry(QRect(140, 190, 48, 25));
        m_axiomBox = new QLineEdit(Parameters);
        m_axiomBox->setObjectName(QStringLiteral("m_axiomBox"));
        m_axiomBox->setGeometry(QRect(60, 250, 141, 24));
        m_constantsBox = new QLineEdit(Parameters);
        m_constantsBox->setObjectName(QStringLiteral("m_constantsBox"));
        m_constantsBox->setGeometry(QRect(60, 280, 141, 24));
        m_rule1Box = new QLineEdit(Parameters);
        m_rule1Box->setObjectName(QStringLiteral("m_rule1Box"));
        m_rule1Box->setGeometry(QRect(60, 320, 141, 24));
        m_rule2Box = new QLineEdit(Parameters);
        m_rule2Box->setObjectName(QStringLiteral("m_rule2Box"));
        m_rule2Box->setGeometry(QRect(60, 350, 141, 24));
        m_rule3Box = new QLineEdit(Parameters);
        m_rule3Box->setObjectName(QStringLiteral("m_rule3Box"));
        m_rule3Box->setGeometry(QRect(60, 380, 141, 24));
        m_rule4Box = new QLineEdit(Parameters);
        m_rule4Box->setObjectName(QStringLiteral("m_rule4Box"));
        m_rule4Box->setGeometry(QRect(60, 410, 141, 24));
        m_rule5Box = new QLineEdit(Parameters);
        m_rule5Box->setObjectName(QStringLiteral("m_rule5Box"));
        m_rule5Box->setGeometry(QRect(60, 440, 141, 24));
        m_radiusSlider = new QSlider(Parameters);
        m_radiusSlider->setObjectName(QStringLiteral("m_radiusSlider"));
        m_radiusSlider->setGeometry(QRect(100, 30, 84, 15));
        m_radiusSlider->setValue(0);
        m_radiusSlider->setOrientation(Qt::Horizontal);
        m_detailLvlBox = new QSpinBox(Parameters);
        m_detailLvlBox->setObjectName(QStringLiteral("m_detailLvlBox"));
        m_detailLvlBox->setGeometry(QRect(140, 70, 48, 25));
        m_detailLvlBox->setValue(0);
        label = new QLabel(Parameters);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 60, 16));
        label_2 = new QLabel(Parameters);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 70, 91, 21));
        label_3 = new QLabel(Parameters);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 130, 60, 21));
        label_4 = new QLabel(Parameters);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 160, 60, 31));
        label_5 = new QLabel(Parameters);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 190, 60, 31));
        label_6 = new QLabel(Parameters);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 250, 51, 21));
        label_7 = new QLabel(Parameters);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 280, 60, 21));
        label_8 = new QLabel(Parameters);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 320, 60, 21));
        label_9 = new QLabel(Parameters);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 350, 60, 21));
        label_10 = new QLabel(Parameters);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 380, 60, 21));
        label_11 = new QLabel(Parameters);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 410, 60, 21));
        label_12 = new QLabel(Parameters);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 440, 60, 21));
        tabWidget->addTab(Parameters, QString());
        Exports = new QWidget();
        Exports->setObjectName(QStringLiteral("Exports"));
        m_expLsysButton = new QPushButton(Exports);
        m_expLsysButton->setObjectName(QStringLiteral("m_expLsysButton"));
        m_expLsysButton->setGeometry(QRect(40, 120, 131, 24));
        m_expParamButton = new QPushButton(Exports);
        m_expParamButton->setObjectName(QStringLiteral("m_expParamButton"));
        m_expParamButton->setGeometry(QRect(40, 200, 131, 24));
        m_exportObjButton = new QPushButton(Exports);
        m_exportObjButton->setObjectName(QStringLiteral("m_exportObjButton"));
        m_exportObjButton->setGeometry(QRect(40, 280, 131, 24));
        tabWidget->addTab(Exports, QString());

        gridLayout->addWidget(tabWidget, 1, 2, 1, 1);

        m_filePathButton = new QPushButton(m_centralWidget);
        m_filePathButton->setObjectName(QStringLiteral("m_filePathButton"));

        gridLayout->addWidget(m_filePathButton, 0, 2, 1, 1);

        m_buildButton = new QPushButton(m_centralWidget);
        m_buildButton->setObjectName(QStringLiteral("m_buildButton"));

        gridLayout->addWidget(m_buildButton, 5, 2, 1, 1);

        m_wireframeCheckBox = new QCheckBox(m_centralWidget);
        m_wireframeCheckBox->setObjectName(QStringLiteral("m_wireframeCheckBox"));

        gridLayout->addWidget(m_wireframeCheckBox, 5, 0, 1, 1);

        m_meshInfoCheckBox = new QCheckBox(m_centralWidget);
        m_meshInfoCheckBox->setObjectName(QStringLiteral("m_meshInfoCheckBox"));
        m_meshInfoCheckBox->setChecked(true);
        m_meshInfoCheckBox->setTristate(false);

        gridLayout->addWidget(m_meshInfoCheckBox, 2, 0, 1, 1);

        MainWindow->setCentralWidget(m_centralWidget);
        m_menuBar = new QMenuBar(MainWindow);
        m_menuBar->setObjectName(QStringLiteral("m_menuBar"));
        m_menuBar->setGeometry(QRect(0, 0, 857, 22));
        MainWindow->setMenuBar(m_menuBar);
        m_mainToolBar = new QToolBar(MainWindow);
        m_mainToolBar->setObjectName(QStringLiteral("m_mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, m_mainToolBar);
        m_statusBar = new QStatusBar(MainWindow);
        m_statusBar->setObjectName(QStringLiteral("m_statusBar"));
        MainWindow->setStatusBar(m_statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        m_toggleInstantCheckBox->setText(QApplication::translate("MainWindow", "Instant Changes Mode", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Radius:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Subdivisions:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Angle:", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Step:", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Iterations:", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Axiom:", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Consts:", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Rule1:", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Rule2:", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Rule3:", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "Rule4:", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Rule5:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Parameters), QApplication::translate("MainWindow", "Parameters", Q_NULLPTR));
        m_expLsysButton->setText(QApplication::translate("MainWindow", "Export Results ", Q_NULLPTR));
        m_expParamButton->setText(QApplication::translate("MainWindow", "Export LSystem ", Q_NULLPTR));
        m_exportObjButton->setText(QApplication::translate("MainWindow", "Export .obj", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Exports), QApplication::translate("MainWindow", "Exports", Q_NULLPTR));
        m_filePathButton->setText(QApplication::translate("MainWindow", "Build LSys From File", Q_NULLPTR));
        m_buildButton->setText(QApplication::translate("MainWindow", "Build LSys From UI", Q_NULLPTR));
        m_wireframeCheckBox->setText(QApplication::translate("MainWindow", "Wireframe", Q_NULLPTR));
        m_meshInfoCheckBox->setText(QApplication::translate("MainWindow", "Vertex Count", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

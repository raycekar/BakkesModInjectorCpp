/********************************************************************************
** Form generated from reading UI file 'BakkesModInjectorCpp.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BAKKESMODINJECTORCPP_H
#define UI_BAKKESMODINJECTORCPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BakkesModInjectorCppClass
{
public:
    QAction *actionOpen_BakkesMod_folder;
    QAction *actionInstall_Python_support;
    QAction *actionReinstall;
    QAction *actionExit;
    QAction *actionBakkesMod_Twitter;
    QAction *actionBakkesMod_com;
    QAction *actionBakkesMod_Discord;
    QAction *actionCheck_injection;
    QAction *actionEnable_safe_mode;
    QAction *actionRun_on_startup;
    QAction *actionHide_when_minimized;
    QAction *actionMinimize_on_start;
    QWidget *centralWidget;
    QLabel *label;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuLinks;
    QMenu *menuHelp;
    QMenu *menuSettings;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BakkesModInjectorCppClass)
    {
        if (BakkesModInjectorCppClass->objectName().isEmpty())
            BakkesModInjectorCppClass->setObjectName(QStringLiteral("BakkesModInjectorCppClass"));
        BakkesModInjectorCppClass->resize(310, 85);
        actionOpen_BakkesMod_folder = new QAction(BakkesModInjectorCppClass);
        actionOpen_BakkesMod_folder->setObjectName(QStringLiteral("actionOpen_BakkesMod_folder"));
        actionInstall_Python_support = new QAction(BakkesModInjectorCppClass);
        actionInstall_Python_support->setObjectName(QStringLiteral("actionInstall_Python_support"));
        actionReinstall = new QAction(BakkesModInjectorCppClass);
        actionReinstall->setObjectName(QStringLiteral("actionReinstall"));
        actionExit = new QAction(BakkesModInjectorCppClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionBakkesMod_Twitter = new QAction(BakkesModInjectorCppClass);
        actionBakkesMod_Twitter->setObjectName(QStringLiteral("actionBakkesMod_Twitter"));
        actionBakkesMod_com = new QAction(BakkesModInjectorCppClass);
        actionBakkesMod_com->setObjectName(QStringLiteral("actionBakkesMod_com"));
        actionBakkesMod_Discord = new QAction(BakkesModInjectorCppClass);
        actionBakkesMod_Discord->setObjectName(QStringLiteral("actionBakkesMod_Discord"));
        actionCheck_injection = new QAction(BakkesModInjectorCppClass);
        actionCheck_injection->setObjectName(QStringLiteral("actionCheck_injection"));
        actionEnable_safe_mode = new QAction(BakkesModInjectorCppClass);
        actionEnable_safe_mode->setObjectName(QStringLiteral("actionEnable_safe_mode"));
        actionEnable_safe_mode->setCheckable(true);
        actionRun_on_startup = new QAction(BakkesModInjectorCppClass);
        actionRun_on_startup->setObjectName(QStringLiteral("actionRun_on_startup"));
        actionRun_on_startup->setCheckable(true);
        actionHide_when_minimized = new QAction(BakkesModInjectorCppClass);
        actionHide_when_minimized->setObjectName(QStringLiteral("actionHide_when_minimized"));
        actionHide_when_minimized->setCheckable(true);
        actionMinimize_on_start = new QAction(BakkesModInjectorCppClass);
        actionMinimize_on_start->setObjectName(QStringLiteral("actionMinimize_on_start"));
        actionMinimize_on_start->setCheckable(true);
        centralWidget = new QWidget(BakkesModInjectorCppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 251, 41));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(80, 10, 211, 23));
        progressBar->setValue(24);
        BakkesModInjectorCppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BakkesModInjectorCppClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 310, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuLinks = new QMenu(menuBar);
        menuLinks->setObjectName(QStringLiteral("menuLinks"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        BakkesModInjectorCppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BakkesModInjectorCppClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BakkesModInjectorCppClass->addToolBar(Qt::BottomToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BakkesModInjectorCppClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BakkesModInjectorCppClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuLinks->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen_BakkesMod_folder);
        menuFile->addAction(actionInstall_Python_support);
        menuFile->addAction(actionReinstall);
        menuFile->addAction(actionExit);
        menuLinks->addAction(actionBakkesMod_com);
        menuLinks->addAction(actionBakkesMod_Twitter);
        menuLinks->addAction(actionBakkesMod_Discord);
        menuHelp->addAction(actionCheck_injection);
        menuSettings->addAction(actionEnable_safe_mode);
        menuSettings->addAction(actionRun_on_startup);
        menuSettings->addAction(actionHide_when_minimized);
        menuSettings->addAction(actionMinimize_on_start);

        retranslateUi(BakkesModInjectorCppClass);
        QObject::connect(actionOpen_BakkesMod_folder, SIGNAL(triggered()), BakkesModInjectorCppClass, SLOT(OnOpenBakkesModFolderClicked()));
        QObject::connect(actionCheck_injection, SIGNAL(triggered()), BakkesModInjectorCppClass, SLOT(OnCheckInjection()));
        QObject::connect(actionEnable_safe_mode, SIGNAL(triggered()), BakkesModInjectorCppClass, SLOT(OnCheckSafeMode()));
        QObject::connect(actionRun_on_startup, SIGNAL(triggered()), BakkesModInjectorCppClass, SLOT(OnRunOnStartup()));
        QObject::connect(actionHide_when_minimized, SIGNAL(triggered()), BakkesModInjectorCppClass, SLOT(OnHideOnMinimize()));
        QObject::connect(actionMinimize_on_start, SIGNAL(triggered()), BakkesModInjectorCppClass, SLOT(OnMinimizeOnStart()));
        QObject::connect(actionExit, SIGNAL(triggered()), BakkesModInjectorCppClass, SLOT(OnExitClick()));
        QObject::connect(actionReinstall, SIGNAL(triggered()), BakkesModInjectorCppClass, SLOT(OnReinstallClick()));
        QObject::connect(actionInstall_Python_support, SIGNAL(triggered()), BakkesModInjectorCppClass, SLOT(OnPythonInstallClick()));

        QMetaObject::connectSlotsByName(BakkesModInjectorCppClass);
    } // setupUi

    void retranslateUi(QMainWindow *BakkesModInjectorCppClass)
    {
        BakkesModInjectorCppClass->setWindowTitle(QApplication::translate("BakkesModInjectorCppClass", "BakkesModInjectorCpp", nullptr));
        actionOpen_BakkesMod_folder->setText(QApplication::translate("BakkesModInjectorCppClass", "Open BakkesMod folder", nullptr));
        actionInstall_Python_support->setText(QApplication::translate("BakkesModInjectorCppClass", "Install Python support", nullptr));
        actionReinstall->setText(QApplication::translate("BakkesModInjectorCppClass", "Reinstall", nullptr));
        actionExit->setText(QApplication::translate("BakkesModInjectorCppClass", "Exit", nullptr));
        actionBakkesMod_Twitter->setText(QApplication::translate("BakkesModInjectorCppClass", "BakkesMod Twitter", nullptr));
        actionBakkesMod_com->setText(QApplication::translate("BakkesModInjectorCppClass", "BakkesMod.com", nullptr));
        actionBakkesMod_Discord->setText(QApplication::translate("BakkesModInjectorCppClass", "BakkesMod Discord", nullptr));
        actionCheck_injection->setText(QApplication::translate("BakkesModInjectorCppClass", "Check injection", nullptr));
        actionEnable_safe_mode->setText(QApplication::translate("BakkesModInjectorCppClass", "Enable safe mode", nullptr));
        actionRun_on_startup->setText(QApplication::translate("BakkesModInjectorCppClass", "Run on startup", nullptr));
        actionHide_when_minimized->setText(QApplication::translate("BakkesModInjectorCppClass", "Hide when minimized", nullptr));
        actionMinimize_on_start->setText(QApplication::translate("BakkesModInjectorCppClass", "Minimize on start", nullptr));
        label->setText(QApplication::translate("BakkesModInjectorCppClass", "TextLabel", nullptr));
        menuFile->setTitle(QApplication::translate("BakkesModInjectorCppClass", "File", nullptr));
        menuLinks->setTitle(QApplication::translate("BakkesModInjectorCppClass", "Links", nullptr));
        menuHelp->setTitle(QApplication::translate("BakkesModInjectorCppClass", "Help", nullptr));
        menuSettings->setTitle(QApplication::translate("BakkesModInjectorCppClass", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BakkesModInjectorCppClass: public Ui_BakkesModInjectorCppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BAKKESMODINJECTORCPP_H

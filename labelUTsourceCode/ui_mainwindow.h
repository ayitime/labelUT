/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCreate_Box;
    QAction *actionOpen;
    QAction *actionOpen_Dir;
    QAction *actionChange_Save_Dir;
    QAction *actionOpen_Annotation;
    QAction *actiontmp;
    QAction *actionymp;
    QAction *actiontmp_2;
    QAction *actionQuit;
    QAction *actionEdit_Label;
    QAction *actionDupulcate_RectBox;
    QAction *actionDelete_Box;
    QAction *actionabout_labelUT;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFrame *frameNavigator;
    QVBoxLayout *verticalLayout;
    QToolButton *toolButton_OpenDir;
    QToolButton *toolButton_ChangeSaveDir;
    QHBoxLayout *horizontalLayout;
    QLabel *imgLight_1;
    QLabel *label_7;
    QLabel *txtLight_2;
    QLabel *label_8;
    QToolButton *toolButton_NextImg;
    QToolButton *toolButton_BefImg;
    QToolButton *toolButton_Save;
    QFrame *line_3;
    QToolButton *toolButton_DrawRect;
    QToolButton *toolButton_DrawGate;
    QToolButton *toolButton_DeleteBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QGraphicsView *graphicsView_Bscan;
    QLabel *label_4;
    QGraphicsView *graphicsView_Cscan;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_6;
    QScrollArea *scrollArea_B;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QScrollArea *scrollArea_C;
    QWidget *scrollAreaWidgetContents_4;
    QFrame *line;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QListWidget *fileListWidgetB;
    QLabel *label_2;
    QListWidget *fileListWidgetC;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1174, 698);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setWindowOpacity(8.000000000000000);
        actionCreate_Box = new QAction(MainWindow);
        actionCreate_Box->setObjectName(QString::fromUtf8("actionCreate_Box"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/labels.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_Box->setIcon(icon1);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon2);
        actionOpen_Dir = new QAction(MainWindow);
        actionOpen_Dir->setObjectName(QString::fromUtf8("actionOpen_Dir"));
        actionOpen_Dir->setIcon(icon2);
        actionChange_Save_Dir = new QAction(MainWindow);
        actionChange_Save_Dir->setObjectName(QString::fromUtf8("actionChange_Save_Dir"));
        actionChange_Save_Dir->setIcon(icon2);
        actionOpen_Annotation = new QAction(MainWindow);
        actionOpen_Annotation->setObjectName(QString::fromUtf8("actionOpen_Annotation"));
        actionOpen_Annotation->setIcon(icon2);
        actiontmp = new QAction(MainWindow);
        actiontmp->setObjectName(QString::fromUtf8("actiontmp"));
        actionymp = new QAction(MainWindow);
        actionymp->setObjectName(QString::fromUtf8("actionymp"));
        actiontmp_2 = new QAction(MainWindow);
        actiontmp_2->setObjectName(QString::fromUtf8("actiontmp_2"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/quit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon3);
        actionEdit_Label = new QAction(MainWindow);
        actionEdit_Label->setObjectName(QString::fromUtf8("actionEdit_Label"));
        actionDupulcate_RectBox = new QAction(MainWindow);
        actionDupulcate_RectBox->setObjectName(QString::fromUtf8("actionDupulcate_RectBox"));
        actionDelete_Box = new QAction(MainWindow);
        actionDelete_Box->setObjectName(QString::fromUtf8("actionDelete_Box"));
        actionDelete_Box->setIcon(icon1);
        actionabout_labelUT = new QAction(MainWindow);
        actionabout_labelUT->setObjectName(QString::fromUtf8("actionabout_labelUT"));
        actionabout_labelUT->setIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frameNavigator = new QFrame(centralwidget);
        frameNavigator->setObjectName(QString::fromUtf8("frameNavigator"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frameNavigator->sizePolicy().hasHeightForWidth());
        frameNavigator->setSizePolicy(sizePolicy);
        frameNavigator->setMaximumSize(QSize(150, 16777215));
        frameNavigator->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: 1px solid rgb(175, 175, 175);  /* \350\256\276\347\275\256\346\267\261\347\201\260\350\211\262\347\232\204\350\276\271\346\241\206 */\n"
"    background-color: #f0f0f0;    /* \350\256\276\347\275\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}"));
        frameNavigator->setFrameShape(QFrame::StyledPanel);
        frameNavigator->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frameNavigator);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toolButton_OpenDir = new QToolButton(frameNavigator);
        toolButton_OpenDir->setObjectName(QString::fromUtf8("toolButton_OpenDir"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolButton_OpenDir->sizePolicy().hasHeightForWidth());
        toolButton_OpenDir->setSizePolicy(sizePolicy1);
        toolButton_OpenDir->setMinimumSize(QSize(0, 0));
        toolButton_OpenDir->setMaximumSize(QSize(16777215, 16777215));
        toolButton_OpenDir->setIcon(icon2);
        toolButton_OpenDir->setIconSize(QSize(40, 40));
        toolButton_OpenDir->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_OpenDir->setAutoRaise(true);

        verticalLayout->addWidget(toolButton_OpenDir);

        toolButton_ChangeSaveDir = new QToolButton(frameNavigator);
        toolButton_ChangeSaveDir->setObjectName(QString::fromUtf8("toolButton_ChangeSaveDir"));
        sizePolicy1.setHeightForWidth(toolButton_ChangeSaveDir->sizePolicy().hasHeightForWidth());
        toolButton_ChangeSaveDir->setSizePolicy(sizePolicy1);
        toolButton_ChangeSaveDir->setIcon(icon2);
        toolButton_ChangeSaveDir->setIconSize(QSize(40, 40));
        toolButton_ChangeSaveDir->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_ChangeSaveDir->setAutoRaise(true);

        verticalLayout->addWidget(toolButton_ChangeSaveDir);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        imgLight_1 = new QLabel(frameNavigator);
        imgLight_1->setObjectName(QString::fromUtf8("imgLight_1"));
        imgLight_1->setMinimumSize(QSize(18, 18));
        imgLight_1->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	min-width: 16px; \n"
"	min-height: 16px;\n"
"	max-width:16px; \n"
"	max-height: 16px;\n"
"	border-radius: 8px;  \n"
"	border:1px solid gray;\n"
"}"));

        horizontalLayout->addWidget(imgLight_1);

        label_7 = new QLabel(frameNavigator);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);
        label_7->setStyleSheet(QString::fromUtf8("border: none;"));

        horizontalLayout->addWidget(label_7);

        txtLight_2 = new QLabel(frameNavigator);
        txtLight_2->setObjectName(QString::fromUtf8("txtLight_2"));
        txtLight_2->setMinimumSize(QSize(18, 18));
        txtLight_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	min-width: 16px; \n"
"	min-height: 16px;\n"
"	max-width:16px; \n"
"	max-height: 16px;\n"
"	border-radius: 8px;  \n"
"	border:1px solid gray;\n"
"}"));

        horizontalLayout->addWidget(txtLight_2);

        label_8 = new QLabel(frameNavigator);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);
        label_8->setStyleSheet(QString::fromUtf8("border: none;"));

        horizontalLayout->addWidget(label_8);


        verticalLayout->addLayout(horizontalLayout);

        toolButton_NextImg = new QToolButton(frameNavigator);
        toolButton_NextImg->setObjectName(QString::fromUtf8("toolButton_NextImg"));
        sizePolicy1.setHeightForWidth(toolButton_NextImg->sizePolicy().hasHeightForWidth());
        toolButton_NextImg->setSizePolicy(sizePolicy1);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_NextImg->setIcon(icon4);
        toolButton_NextImg->setIconSize(QSize(40, 40));
        toolButton_NextImg->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_NextImg->setAutoRaise(true);

        verticalLayout->addWidget(toolButton_NextImg);

        toolButton_BefImg = new QToolButton(frameNavigator);
        toolButton_BefImg->setObjectName(QString::fromUtf8("toolButton_BefImg"));
        sizePolicy1.setHeightForWidth(toolButton_BefImg->sizePolicy().hasHeightForWidth());
        toolButton_BefImg->setSizePolicy(sizePolicy1);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/prev.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_BefImg->setIcon(icon5);
        toolButton_BefImg->setIconSize(QSize(40, 40));
        toolButton_BefImg->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_BefImg->setAutoRaise(true);

        verticalLayout->addWidget(toolButton_BefImg);

        toolButton_Save = new QToolButton(frameNavigator);
        toolButton_Save->setObjectName(QString::fromUtf8("toolButton_Save"));
        sizePolicy1.setHeightForWidth(toolButton_Save->sizePolicy().hasHeightForWidth());
        toolButton_Save->setSizePolicy(sizePolicy1);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Save->setIcon(icon6);
        toolButton_Save->setIconSize(QSize(40, 40));
        toolButton_Save->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_Save->setAutoRaise(true);

        verticalLayout->addWidget(toolButton_Save);

        line_3 = new QFrame(frameNavigator);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setStyleSheet(QString::fromUtf8(""));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        toolButton_DrawRect = new QToolButton(frameNavigator);
        toolButton_DrawRect->setObjectName(QString::fromUtf8("toolButton_DrawRect"));
        sizePolicy1.setHeightForWidth(toolButton_DrawRect->sizePolicy().hasHeightForWidth());
        toolButton_DrawRect->setSizePolicy(sizePolicy1);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/objects.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_DrawRect->setIcon(icon7);
        toolButton_DrawRect->setIconSize(QSize(40, 40));
        toolButton_DrawRect->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_DrawRect->setAutoRaise(true);

        verticalLayout->addWidget(toolButton_DrawRect);

        toolButton_DrawGate = new QToolButton(frameNavigator);
        toolButton_DrawGate->setObjectName(QString::fromUtf8("toolButton_DrawGate"));
        sizePolicy1.setHeightForWidth(toolButton_DrawGate->sizePolicy().hasHeightForWidth());
        toolButton_DrawGate->setSizePolicy(sizePolicy1);
        toolButton_DrawGate->setIcon(icon7);
        toolButton_DrawGate->setIconSize(QSize(40, 40));
        toolButton_DrawGate->setCheckable(true);
        toolButton_DrawGate->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_DrawGate->setAutoRaise(true);

        verticalLayout->addWidget(toolButton_DrawGate);

        toolButton_DeleteBox = new QToolButton(frameNavigator);
        toolButton_DeleteBox->setObjectName(QString::fromUtf8("toolButton_DeleteBox"));
        sizePolicy1.setHeightForWidth(toolButton_DeleteBox->sizePolicy().hasHeightForWidth());
        toolButton_DeleteBox->setSizePolicy(sizePolicy1);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_DeleteBox->setIcon(icon8);
        toolButton_DeleteBox->setIconSize(QSize(40, 40));
        toolButton_DeleteBox->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton_DeleteBox->setAutoRaise(true);

        verticalLayout->addWidget(toolButton_DeleteBox);


        gridLayout->addWidget(frameNavigator, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        graphicsView_Bscan = new QGraphicsView(centralwidget);
        graphicsView_Bscan->setObjectName(QString::fromUtf8("graphicsView_Bscan"));
        graphicsView_Bscan->setMouseTracking(false);

        verticalLayout_2->addWidget(graphicsView_Bscan);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        graphicsView_Cscan = new QGraphicsView(centralwidget);
        graphicsView_Cscan->setObjectName(QString::fromUtf8("graphicsView_Cscan"));
        graphicsView_Cscan->setMouseTracking(false);

        verticalLayout_2->addWidget(graphicsView_Cscan);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_4->addWidget(label_6);

        scrollArea_B = new QScrollArea(centralwidget);
        scrollArea_B->setObjectName(QString::fromUtf8("scrollArea_B"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollArea_B->sizePolicy().hasHeightForWidth());
        scrollArea_B->setSizePolicy(sizePolicy2);
        scrollArea_B->setMinimumSize(QSize(300, 0));
        scrollArea_B->setMaximumSize(QSize(400, 16777215));
        scrollArea_B->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 298, 85));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        scrollArea_B->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_4->addWidget(scrollArea_B);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_4->addWidget(label_5);

        scrollArea_C = new QScrollArea(centralwidget);
        scrollArea_C->setObjectName(QString::fromUtf8("scrollArea_C"));
        sizePolicy2.setHeightForWidth(scrollArea_C->sizePolicy().hasHeightForWidth());
        scrollArea_C->setSizePolicy(sizePolicy2);
        scrollArea_C->setMinimumSize(QSize(300, 0));
        scrollArea_C->setMaximumSize(QSize(400, 16777215));
        scrollArea_C->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 298, 85));
        scrollArea_C->setWidget(scrollAreaWidgetContents_4);

        verticalLayout_4->addWidget(scrollArea_C);


        verticalLayout_5->addLayout(verticalLayout_4);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label);

        fileListWidgetB = new QListWidget(centralwidget);
        fileListWidgetB->setObjectName(QString::fromUtf8("fileListWidgetB"));
        sizePolicy.setHeightForWidth(fileListWidgetB->sizePolicy().hasHeightForWidth());
        fileListWidgetB->setSizePolicy(sizePolicy);
        fileListWidgetB->setMinimumSize(QSize(300, 0));

        verticalLayout_3->addWidget(fileListWidgetB);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        fileListWidgetC = new QListWidget(centralwidget);
        fileListWidgetC->setObjectName(QString::fromUtf8("fileListWidgetC"));
        sizePolicy.setHeightForWidth(fileListWidgetC->sizePolicy().hasHeightForWidth());
        fileListWidgetC->setSizePolicy(sizePolicy);
        fileListWidgetC->setMinimumSize(QSize(300, 0));

        verticalLayout_3->addWidget(fileListWidgetC);


        verticalLayout_5->addLayout(verticalLayout_3);


        gridLayout->addLayout(verticalLayout_5, 0, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1174, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen_Dir);
        menuFile->addAction(actionChange_Save_Dir);
        menuFile->addAction(actiontmp_2);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuEdit->addAction(actionCreate_Box);
        menuEdit->addAction(actionDelete_Box);
        menuHelp->addAction(actionabout_labelUT);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "labelUT", nullptr));
        actionCreate_Box->setText(QApplication::translate("MainWindow", "Create RectBox", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
        actionOpen_Dir->setText(QApplication::translate("MainWindow", "Open Dir", nullptr));
        actionChange_Save_Dir->setText(QApplication::translate("MainWindow", "Change Save Dir", nullptr));
        actionOpen_Annotation->setText(QApplication::translate("MainWindow", "Open Annotation", nullptr));
        actiontmp->setText(QApplication::translate("MainWindow", "tmp", nullptr));
        actionymp->setText(QApplication::translate("MainWindow", "ymp", nullptr));
        actiontmp_2->setText(QApplication::translate("MainWindow", "To be set", nullptr));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        actionEdit_Label->setText(QApplication::translate("MainWindow", "Edit Label", nullptr));
        actionDupulcate_RectBox->setText(QApplication::translate("MainWindow", "Dupulcate RectBox", nullptr));
        actionDelete_Box->setText(QApplication::translate("MainWindow", "Delete RectBox", nullptr));
        actionabout_labelUT->setText(QApplication::translate("MainWindow", "About labelUT", nullptr));
        toolButton_OpenDir->setText(QApplication::translate("MainWindow", "Open Dir", nullptr));
        toolButton_ChangeSaveDir->setText(QApplication::translate("MainWindow", "Change Save Dir", nullptr));
        imgLight_1->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "Img", nullptr));
        txtLight_2->setText(QString());
        label_8->setText(QApplication::translate("MainWindow", "Txt", nullptr));
        toolButton_NextImg->setText(QApplication::translate("MainWindow", "Next Image", nullptr));
        toolButton_BefImg->setText(QApplication::translate("MainWindow", "Prev Image", nullptr));
        toolButton_Save->setText(QApplication::translate("MainWindow", "Save", nullptr));
        toolButton_DrawRect->setText(QApplication::translate("MainWindow", "CreateRectBox", nullptr));
        toolButton_DrawGate->setText(QApplication::translate("MainWindow", "CreateAlignInfo", nullptr));
        toolButton_DeleteBox->setText(QApplication::translate("MainWindow", "DeleteRectBox", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">B-scan</span></p></body></html>", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">C-scan</span></p></body></html>", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "B-area object info", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "C-area object info", nullptr));
        label->setText(QApplication::translate("MainWindow", "File List B-scan", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "File List C-scan", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", nullptr));
        menuView->setTitle(QApplication::translate("MainWindow", "View", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'classwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLASSWIDGET_H
#define UI_CLASSWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_classWidget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *yesButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QListWidget *listWidget;
    QLineEdit *lineEdit;

    void setupUi(QWidget *classWidget)
    {
        if (classWidget->objectName().isEmpty())
            classWidget->setObjectName(QString::fromUtf8("classWidget"));
        classWidget->resize(341, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        classWidget->setWindowIcon(icon);
        gridLayout = new QGridLayout(classWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(88, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        yesButton = new QPushButton(classWidget);
        yesButton->setObjectName(QString::fromUtf8("yesButton"));

        horizontalLayout->addWidget(yesButton);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelButton = new QPushButton(classWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        listWidget = new QListWidget(classWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 2, 0, 1, 1);

        lineEdit = new QLineEdit(classWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setMinimumSize(QSize(0, 25));
        lineEdit->setMaximumSize(QSize(16777215, 30));

        gridLayout->addWidget(lineEdit, 0, 0, 1, 1);


        retranslateUi(classWidget);

        QMetaObject::connectSlotsByName(classWidget);
    } // setupUi

    void retranslateUi(QWidget *classWidget)
    {
        classWidget->setWindowTitle(QApplication::translate("classWidget", "labelUT", nullptr));
        yesButton->setText(QApplication::translate("classWidget", "OK", nullptr));
        cancelButton->setText(QApplication::translate("classWidget", "Canacel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class classWidget: public Ui_classWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLASSWIDGET_H

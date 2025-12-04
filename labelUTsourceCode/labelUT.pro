QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alignindicatorline.cpp \
    classwidget.cpp \
    draggablehlineitem.cpp \
    gateoverlay.cpp \
    main.cpp \
    mainwindow.cpp \
    rectangleitem.cpp

HEADERS += \
    alignindicatorline.h \
    classwidget.h \
    draggablehlineitem.h \
    gateoverlay.h \
    mainwindow.h \
    rectangleitem.h

FORMS += \
    classwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gamemodel.cpp \
    gameoverride.cpp \
    gameslots.cpp \
    gamewidget.cpp \
    helpwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    modechoosewidget.cpp \
    mycharacter.cpp \
    res.cpp \
    startbutton.cpp \
    tmp.cpp

HEADERS += \
    gamemodel.h \
    gamewidget.h \
    helpwidget.h \
    mainwindow.h \
    modechoosewidget.h \
    mycharacter.h \
    res.h \
    startbutton.h

FORMS += \
    gamewidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc \
    chara.qrc \
    item.qrc \
    maintitle.qrc \
    modebuttons.qrc \
    song.qrc \
    sound.qrc

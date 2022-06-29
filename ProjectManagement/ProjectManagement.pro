QT       += core gui

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
    addmemberwindow.cpp \
    addtaskwindow.cpp \
    chatwindow.cpp \
    createaccountwindow.cpp \
    createprojectwindow.cpp \
    data/database/database.cpp \
    data/model/chat.cpp \
    data/model/project.cpp \
    data/model/task.cpp \
    data/model/user.cpp \
    forgetpasswordwindow.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    projectswindow.cpp \
    settingwindow.cpp \
    utils/exception.cpp

HEADERS += \
    addmemberwindow.h \
    addtaskwindow.h \
    chatwindow.h \
    createaccountwindow.h \
    createprojectwindow.h \
    data/database/database.h \
    data/model/chat.h \
    data/model/project.h \
    data/model/task.h \
    data/model/user.h \
    forgetpasswordwindow.h \
    loginwindow.h \
    mainwindow.h \
    projectswindow.h \
    settingwindow.h \
    utils/exception.h

FORMS += \
    addmemberwindow.ui \
    addtaskwindow.ui \
    chatwindow.ui \
    createaccountwindow.ui \
    createprojectwindow.ui \
    forgetpasswordwindow.ui \
    loginwindow.ui \
    mainwindow.ui \
    projectswindow.ui \
    settingwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



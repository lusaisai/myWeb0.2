#-------------------------------------------------
#
# Project created by QtCreator 2013-02-01T17:22:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MywebAdminQApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connectdialog.cpp \
    lib/topictype.cpp \
    lib/topic.cpp \
    lib/mysqldeliver.cpp \
    lib/list.cpp

HEADERS  += mainwindow.h \
    connectdialog.h \
    lib/topictype.hpp \
    lib/topic.hpp \
    lib/mysqldeliver.hpp \
    lib/list.hpp

FORMS    += mainwindow.ui \
    connectdialog.ui

RESOURCES += \
    resources.qrc

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lmysqlpp

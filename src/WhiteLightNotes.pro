#-------------------------------------------------
#
# Project created by QtCreator 2011-10-17T10:08:21
#
#-------------------------------------------------

QT      += core gui sql

CONFIG += qxt
QXT += qxt gui

include(qst/qst.pri)

TARGET = WhiteLightNotes
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    settings/settingsmanager.cpp \
    handlers/taghandler.cpp \
    handlers/notehandler.cpp \
    notesform.cpp \
    createnoteform.cpp \
    handlers/taggednotehandler.cpp

HEADERS  += mainwindow.h \
    settings/settingsmanager.h \
    handlers/taghandler.h \
    handlers/notehandler.h \
    notesform.h \
    createnoteform.h \
    handlers/taggednotehandler.h

FORMS    += mainwindow.ui \
    notesform.ui \
    createnoteform.ui

RESOURCES += \
    icons.qrc








































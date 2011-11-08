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
    handlers/tagednotehandler.cpp \
    notesform.cpp

HEADERS  += mainwindow.h \
    settings/settingsmanager.h \
    handlers/taghandler.h \
    handlers/notehandler.h \
    handlers/tagednotehandler.h \
    notesform.h

FORMS    += mainwindow.ui \
    notesform.ui

RESOURCES += \
    icons.qrc

































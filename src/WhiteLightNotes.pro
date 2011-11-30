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
    handlers/taghandler.cpp \
    handlers/notehandler.cpp \
    notesform.cpp \
    createnoteform.cpp \
    handlers/taggednotehandler.cpp \
    noteitemdelegate.cpp \
    tagsmodel.cpp \
    notetheme.cpp \
	settings/settingsdialog.cpp \
	settings/settingsmanager.cpp \
    quickfilterparser.cpp

HEADERS  += mainwindow.h \
    handlers/taghandler.h \
    handlers/notehandler.h \
    notesform.h \
    createnoteform.h \
    handlers/taggednotehandler.h \
    noteitemdelegate.h \
    tagsmodel.h \
	notetheme.h \
	settings/settingsdialog.h \
	settings/settingsmanager.h \
    settings/settings.h \
    quickfilterparser.h

FORMS    += mainwindow.ui \
    notesform.ui \
    createnoteform.ui \
    settings/settingsdialog.ui

RESOURCES += \
	icons.qrc

































































































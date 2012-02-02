#/****************************************************************************
#** WhiteLight Notes 0.9 rc2
#** Copyright (C)  Granin A.S. 2011
#** 
#**
#** This file is part of the WhiteLight Notes project.
#**
#** GNU General Public License Usage
#** This file may be used under the terms of the GNU
#** General Public License version 3.0 as published by the Free Software
#** Foundation and appearing in the file LICENSE.GPL3 included in the
#** packaging of this file.  Please review the following information to
#** ensure the GNU General Public License version 3.0 requirements will be
#** met: http://www.gnu.org/licenses/gpl.html.
#**
#** If you have questions regarding the use of this file, please contact
#** authors.
#**
#** Author: Granin, Alexandr
#** graninas@gmail.com
#****************************************************************************/
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
    handlers/taggednotehandler.cpp \
    noteitemdelegate.cpp \
    tagsmodel.cpp \
    notetheme.cpp \
	settings/settingsdialog.cpp \
	settings/settingsmanager.cpp \
    quickfilterparser.cpp \
    aboutdialog.cpp \
    editnoteform.cpp \
    note.cpp \
    statemachine/state.cpp \
    statemachine/event.cpp \
    statemachine/transtable.cpp \
    statemachine/transition.cpp \
    statemachine/statemachine.cpp

HEADERS  += mainwindow.h \
    handlers/taghandler.h \
    handlers/notehandler.h \
    notesform.h \
    handlers/taggednotehandler.h \
    noteitemdelegate.h \
    tagsmodel.h \
	notetheme.h \
	settings/settingsdialog.h \
	settings/settingsmanager.h \
    settings/settings.h \
    quickfilterparser.h \
    aboutdialog.h \
    editnoteform.h \
    note.h \
    statemachine/state.h \
    statemachine/event.h \
    statemachine/transtable.h \
    statemachine/transition.h \
    statemachine/statemachine.h \
    types.h \
    noteshowingtemplate.h

FORMS    += mainwindow.ui \
    notesform.ui \
    settings/settingsdialog.ui \
    aboutdialog.ui \
    editnoteform.ui

RESOURCES += \
	icons.qrc






































































































































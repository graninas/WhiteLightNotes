/****************************************************************************
** WhiteLight Notes 0.9 rc1
** Copyright (C)  Granin A.S. 2011
** 
**
** This file is part of the WhiteLight Notes project.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3 included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/licenses/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** authors.
**
** Author: Granin, Alexandr
** graninas@gmail.com
****************************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMap>
#include <QVariant>
#include <QString>

typedef QMap<QString, QVariant> SettingsMap;

const QString S_DATABASE_FILE_NAME     = "DatabaseFileName";
const QString S_IS_FIRST_RUN           = "IsFirstRun";
const QString S_LANGUAGE               = "Language";
const QString S_NEW_NOTE_TEXT_TEMPLATE = "NewNoteTextTemplate";
const QString S_NOTE_SHOWING_TEMPLATE  = "NoteShowingTemplate";

const QString S_CHANGE_FONT_SIZE_STEP  = "ChangeFontSizeStep";
const QString S_DEFAULT_COLOR_THEME    = "DefaultColorTheme";
const QString S_DEFAULT_FILTERING_BY   = "DefaultFilteringBy";
const QString S_ENABLE_NOTE_TITLES     = "EnableNoteTitles";
const QString S_ALLOW_DATE_EDITING_IN_NEW_NOTE = "AllowDateEditingInNewNote";

const QString DEFAULT_DATABASE_FILE_NAME = "WhiteLightNotes.db";


#endif // SETTINGS_H

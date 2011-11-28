#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMap>
#include <QVariant>
#include <QString>

typedef QMap<QString, QVariant> SettingsMap;

const QString S_DATABASE_FILE_NAME     = "DatabaseFileName";
const QString S_IS_FIRST_RUN           = "IsFirstRun";
const QString S_CHANGE_FONT_SIZE_STEP  = "ChangeFontSizeStep";
const QString S_DEFAULT_COLOR_THEME    = "DefaultColorTheme";
const QString S_NEW_NOTE_TEXT_TEMPLATE = "NewNoteTextTemplate";
const QString S_NOTE_SHOWING_TEMPLATE  = "NoteShowingTemplate";


const QString DEFAULT_DATABASE_FILE_NAME = "WhiteLightNotes.db";

#endif // SETTINGS_H

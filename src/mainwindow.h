/****************************************************************************
** WhiteLight Notes 0.9 rc2
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSystemTrayIcon>
#include <QMenu>
#include <QFile>

#include "notesform.h"
#include "editnoteform.h"
#include "notetheme.h"

#include "settings/settings.h"

#include <QxtGui/qxtgui.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	void createForms(NotesForm * notesForm,
					 EditNoteForm *editNoteForm = NULL);
	void setupForms(const SettingsMap &settings);

public slots:

	void showTrayIcon();

	void notesFormShowChange();
	void editNoteFormShowChange();
	void newNote();
	void editNote(const Note &note);

	void trayIconClicked(const QSystemTrayIcon::ActivationReason & reason);
	void closeApplication();

	void loadAll();

	void showSettingsDialog();
	void showAboutDialog();

	void finishNote(const Note &note);
	void cancelEditing();
	void changeColorTheme(const Note &note, const QString &newTheme);

private:
    Ui::MainWindow *ui;

	NotesForm    *_notesForm;
	EditNoteForm *_editNoteForm;

	QSystemTrayIcon _trayIcon;
	QMenu _trayIconContextMenu;

	QxtGlobalShortcut _notesHotkey;
	QxtGlobalShortcut _createNoteHotkey;
	QxtGlobalShortcut _closeAppHotkey;
};

#endif // MAINWINDOW_H

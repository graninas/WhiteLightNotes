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

	void setSettings(const SettingsMap &settings);

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

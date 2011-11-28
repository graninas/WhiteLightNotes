#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSystemTrayIcon>
#include <QMenu>
#include <QFile>

#include "notesform.h"
#include "createnoteform.h"
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
	void createNoteFormShowChange();
	void createNote();

	void trayIconClicked(const QSystemTrayIcon::ActivationReason & reason);
	void closeApplication();

	void loadAll();

	void showSettingsDialog();

private:
    Ui::MainWindow *ui;

	NotesForm      *_notesForm;
	CreateNoteForm *_createNoteForm;

	QSystemTrayIcon _trayIcon;
	QMenu _trayIconContextMenu;

	QxtGlobalShortcut _notesHotkey;
	QxtGlobalShortcut _CreateNoteHotkey;
	QxtGlobalShortcut _closeAppHotkey;
};

#endif // MAINWINDOW_H

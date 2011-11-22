#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSystemTrayIcon>
#include <QMenu>
#include <QFile>

#include "notesform.h"
#include "createnoteform.h"

// Qxt works only if it compiled into Qt.
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

public slots:

	void showTrayIcon();

	void notesFormShowChange();
	void createNoteFormShowChange();
	void createNote();

	void trayIconClicked(const QSystemTrayIcon::ActivationReason & reason);
	void closeApplication();

	void loadAll();

private:
    Ui::MainWindow *ui;

	NotesForm *_notesForm;
	CreateNoteForm *_createNoteForm;

	QSystemTrayIcon _trayIcon;
	QMenu _trayIconContextMenu;

	QxtGlobalShortcut _notesFormHotKeyHandle;
	QxtGlobalShortcut _createNoteFormHotKeyHandle;
	QxtGlobalShortcut _closeApplicationKeyHandle;

	QString _getTitleTemplate() const;
	QString _getNoteTemplate() const;
	QString _getTagsTemplate() const;

	QString _readFromFile(QFile *file) const;

};

#endif // MAINWINDOW_H

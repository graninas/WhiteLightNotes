#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include <QTextStream>
#include <QFile>

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	_notesForm = new NotesForm(this);
	_createNoteForm = new CreateNoteForm(this);
	Q_ASSERT(_notesForm != NULL);
	Q_ASSERT(_createNoteForm != NULL);

	_createNoteForm->setNoteTemplate(_getNoteTemplate());

	connect(_createNoteForm, SIGNAL(noteCreated()),
			_notesForm, SLOT(loadAll()));

	_trayIconContextMenu.addAction(ui->action_AddNote);
	_trayIconContextMenu.addAction(ui->action_ShowNotes);
	_trayIconContextMenu.addAction(ui->action_Settings);
	_trayIconContextMenu.addSeparator();
	_trayIconContextMenu.addAction(ui->action_About);
	_trayIcon.setIcon(QIcon(":icons/resources/notebook.png"));
	_trayIcon.setContextMenu(&_trayIconContextMenu);

	_notesFormHotKeyHandle.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_1));
	_notesFormHotKeyHandle.setEnabled(true);
	connect(&_notesFormHotKeyHandle, SIGNAL(activated()),
			this, SLOT(showNotesForm()));

	_createNoteFormHotKeyHandle.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_2));
	_createNoteFormHotKeyHandle.setEnabled(true);
	connect(&_createNoteFormHotKeyHandle, SIGNAL(activated()),
			this, SLOT(showCreateNoteForm()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTrayIcon()
{
	_trayIcon.show();
}

void MainWindow::showNotesForm()
{
	Q_ASSERT(_notesForm != NULL);
	_notesForm->show();
}

void MainWindow::showCreateNoteForm()
{
	Q_ASSERT(_createNoteForm != NULL);
	_createNoteForm->resetEditFields();
	_createNoteForm->show();
}

QString MainWindow::_getNoteTemplate()
{
	QFile templFile(QApplication::applicationDirPath()
					   + "\\NoteTemplate.html");
	QString res;
	if (templFile.open(QFile::ReadOnly))
	{
		QTextStream in(&templFile);
		QString line;
		do {
			 in >> line;
			 res += "\n" + line;
		} while (!line.isNull());
	}
return res;
}

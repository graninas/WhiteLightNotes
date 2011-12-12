#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>

#include "settings/settingsdialog.h"
#include "aboutdialog.h"

#include "handlers/taggednotehandler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	_notesForm      = new NotesForm     (this);
	_editNoteForm = new EditNoteForm(this);
	Q_ASSERT(_notesForm      != NULL);
	Q_ASSERT(_editNoteForm != NULL);

	_notesForm   ->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
	_editNoteForm->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);

	QObject::connect(_editNoteForm, SIGNAL(noteCreated()),
					 _notesForm,      SLOT(loadAll()));

	_trayIconContextMenu.addAction(ui->action_NewNote);
	_trayIconContextMenu.addAction(ui->action_Notes);
	_trayIconContextMenu.addAction(ui->action_Settings);
	_trayIconContextMenu.addAction(ui->action_About);
	_trayIconContextMenu.addSeparator();
	_trayIconContextMenu.addAction(ui->action_Exit);
	_trayIcon.setContextMenu(&_trayIconContextMenu);
	_trayIcon.setIcon(QIcon(":icons/resources/notebook.png"));

	QObject::connect(&_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
					 this,   SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason)));

	QObject::connect(ui->action_Exit,     SIGNAL(triggered()), this, SLOT(closeApplication()));
	QObject::connect(ui->action_NewNote,  SIGNAL(triggered()), this, SLOT(newNote()));
	QObject::connect(ui->action_Notes,    SIGNAL(triggered()), this, SLOT(notesFormShowChange()));
	QObject::connect(ui->action_Settings, SIGNAL(triggered()), this, SLOT(showSettingsDialog()));
	QObject::connect(ui->action_About,    SIGNAL(triggered()), this, SLOT(showAboutDialog()));

	_notesHotkey     .setShortcut(QKeySequence(Qt::CTRL + Qt::Key_1));
	_createNoteHotkey.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_2));
	_closeAppHotkey  .setShortcut(QKeySequence(Qt::CTRL + Qt::Key_3));
	_createNoteHotkey.setEnabled(true);
	_notesHotkey     .setEnabled(true);
	_closeAppHotkey  .setEnabled(true);

	QObject::connect(&_notesHotkey,      SIGNAL(activated()), this, SLOT(notesFormShowChange()));
	QObject::connect(&_createNoteHotkey, SIGNAL(activated()), this, SLOT(editNoteFormShowChange()));
	QObject::connect(&_closeAppHotkey,   SIGNAL(activated()), this, SLOT(closeApplication()));

	QObject::connect(_editNoteForm, SIGNAL(finishNote(Note)), this, SLOT(finishNote(Note)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSettings(const SettingsMap &settings)
{
	_editNoteForm->setSettings(settings);
}

void MainWindow::showTrayIcon()
{
	_trayIcon.show();
}

void MainWindow::notesFormShowChange()
{
	Q_ASSERT(_notesForm != NULL);
	if (_notesForm->isVisible())
		_notesForm->close();
	else
	{
		_notesForm->activateWindow();
		_notesForm->show();
	}
}

void MainWindow::editNoteFormShowChange()
{
	Q_ASSERT(_editNoteForm != NULL);

	if (_editNoteForm->isVisible())
		_editNoteForm->close();
	else
		newNote();
}

void MainWindow::newNote()
{
	_editNoteForm->setNote(Note());
	_editNoteForm->activateWindow();
	_editNoteForm->loadAll();
	_editNoteForm->show();
}

void MainWindow::trayIconClicked(const QSystemTrayIcon::ActivationReason & reason)
{
	if (reason == QSystemTrayIcon::Trigger)
		notesFormShowChange();
}

void MainWindow::closeApplication()
{
	QApplication::exit();
}

void MainWindow::loadAll()
{
	Q_ASSERT(_notesForm != NULL);
	Q_ASSERT(_editNoteForm != NULL);
	_notesForm->loadAll();
	_editNoteForm->loadAll();
}

void MainWindow::showSettingsDialog()
{
	SettingsDialog dlg;
	if (dlg.exec() == QDialog::Accepted)
	{
		Q_ASSERT(false);
	}
}

void MainWindow::showAboutDialog()
{
	AboutDialog dlg;
	dlg.exec();
}

void MainWindow::finishNote(const Note &note)
{
	_editNoteForm->close();
	Q_ASSERT(note.isValid());
	QVariant noteID = note.noteID();
	if (noteID.isNull())
		noteID = NoteHandler::createNote(note.title(), note.htmlText(), note.simpleText(),
										 note.date(),  note.theme(),    note.complexText());
	else
		NoteHandler::updateNote(note.noteID(),     note.title(), note.htmlText(),
								note.simpleText(), note.date(),  note.theme(),
								note.complexText());
	Q_ASSERT(noteID.isValid());
	TaggedNoteHandler::updateNoteTags(noteID, note.tagList());
	_notesForm->loadAll();
}

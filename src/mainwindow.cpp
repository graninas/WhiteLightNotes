#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>

#include "settings/settingsdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	_notesForm      = new NotesForm     (this);
	_createNoteForm = new CreateNoteForm(this);
	Q_ASSERT(_notesForm      != NULL);
	Q_ASSERT(_createNoteForm != NULL);

	_notesForm     ->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
	_createNoteForm->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);

	QObject::connect(_createNoteForm, SIGNAL(noteCreated()),
					 _notesForm, SLOT(loadAll()));

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
	QObject::connect(ui->action_NewNote,  SIGNAL(triggered()), this, SLOT(createNote()));
	QObject::connect(ui->action_Notes,    SIGNAL(triggered()), this, SLOT(notesFormShowChange()));
	QObject::connect(ui->action_Settings, SIGNAL(triggered()), this, SLOT(showSettingsDialog()));

	_notesHotkey     .setShortcut(QKeySequence(Qt::CTRL + Qt::Key_1));
	_CreateNoteHotkey.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_2));
	_closeAppHotkey  .setShortcut(QKeySequence(Qt::CTRL + Qt::Key_3));
	_CreateNoteHotkey.setEnabled(true);
	_notesHotkey     .setEnabled(true);
	_closeAppHotkey  .setEnabled(true);

	QObject::connect(&_notesHotkey,      SIGNAL(activated()), this, SLOT(notesFormShowChange()));
	QObject::connect(&_CreateNoteHotkey, SIGNAL(activated()), this, SLOT(createNoteFormShowChange()));
	QObject::connect(&_closeAppHotkey,   SIGNAL(activated()), this, SLOT(closeApplication()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSettings(const SettingsMap &settings)
{
	_createNoteForm->setSettings(settings);
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
		_notesForm->reset();
		_notesForm->show();
	}
}

void MainWindow::createNoteFormShowChange()
{
	Q_ASSERT(_createNoteForm != NULL);

	if (_createNoteForm->isVisible())
		_createNoteForm->cancelCreation();
	else
		createNote();
}

void MainWindow::createNote()
{
	_createNoteForm->activateWindow();
	_createNoteForm->reset();
	_createNoteForm->show();
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
	Q_ASSERT(_createNoteForm != NULL);
	_notesForm->loadAll();
	_createNoteForm->loadTags();
}

void MainWindow::showSettingsDialog()
{
	SettingsDialog dlg;
	if (dlg.exec() == QDialog::Accepted)
	{
		Q_ASSERT(false);
	}
}


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include <QTextStream>
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

	_createNoteForm->setTitleTemplate(_getTitleTemplate());
	_createNoteForm->setNoteTemplate(_getNoteTemplate());
	_createNoteForm->setTagsTemplate(_getTagsTemplate());


	connect(_createNoteForm, SIGNAL(noteCreated()),
			_notesForm, SLOT(loadAll()));

	_trayIconContextMenu.addAction(ui->action_NewNote);
	_trayIconContextMenu.addAction(ui->action_ShowHideNotes);
	_trayIconContextMenu.addAction(ui->action_Settings);
	_trayIconContextMenu.addAction(ui->action_About);
	_trayIconContextMenu.addSeparator();
	_trayIconContextMenu.addAction(ui->action_Exit);
	_trayIcon.setIcon(QIcon(":icons/resources/notebook.png"));
	_trayIcon.setContextMenu(&_trayIconContextMenu);

	QObject::connect(&_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
					 this, SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason)));

	QObject::connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(closeApplication()));
	QObject::connect(ui->action_ShowHideNotes, SIGNAL(triggered()),
					 this, SLOT(notesFormShowChange()));
	QObject::connect(ui->action_NewNote, SIGNAL(triggered()),
					 this, SLOT(createNote()));

	_notesFormHotKeyHandle.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_1));
	_notesFormHotKeyHandle.setEnabled(true);
	connect(&_notesFormHotKeyHandle, SIGNAL(activated()),
			this, SLOT(notesFormShowChange()));

	_createNoteFormHotKeyHandle.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_2));
	_createNoteFormHotKeyHandle.setEnabled(true);
	connect(&_createNoteFormHotKeyHandle, SIGNAL(activated()),
			this, SLOT(createNoteFormShowChange()));

	_closeApplicationKeyHandle.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_3));
	_closeApplicationKeyHandle.setEnabled(true);
	connect(&_closeApplicationKeyHandle, SIGNAL(activated()),
			this, SLOT(closeApplication()));
}

MainWindow::~MainWindow()
{
    delete ui;
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
		_notesForm->show();
		_notesForm->setFocus();
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
	_createNoteForm->resetEditFields();
	_createNoteForm->show();
	_createNoteForm->setFocus();
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
	_notesForm->loadAll();
}

QString MainWindow::_getTitleTemplate() const
{
	QFile templFile(QApplication::applicationDirPath()
					   + "\\resources\\TitleTemplate.html");
	return _readFromFile(&templFile);
}

QString MainWindow::_getNoteTemplate() const
{
	QFile templFile(QApplication::applicationDirPath()
					   + "\\resources\\NoteTemplate.html");
	return _readFromFile(&templFile);
}

QString MainWindow::_getTagsTemplate() const
{
	QFile templFile(QApplication::applicationDirPath()
					   + "\\resources\\TagsTemplate.html");
	return _readFromFile(&templFile);
}

QString MainWindow::_readFromFile(QFile *file) const
{
	QString res;
	Q_ASSERT(file != NULL);
	if (file->open(QFile::ReadOnly))
		res = file->readAll();
	return res;
}

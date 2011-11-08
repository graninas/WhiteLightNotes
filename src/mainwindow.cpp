#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	_notesForm = new NotesForm(this);

	_trayIconContextMenu.addAction(ui->action_AddNote);
	_trayIconContextMenu.addAction(ui->action_ShowNotes);
	_trayIconContextMenu.addAction(ui->action_Settings);
	_trayIconContextMenu.addSeparator();
	_trayIconContextMenu.addAction(ui->action_About);
	_trayIcon.setIcon(QIcon(":icons/resources/notebook.png"));
	_trayIcon.setContextMenu(&_trayIconContextMenu);

	_hotkeyHandle.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_1));
	_hotkeyHandle.setEnabled(true);
	connect(&_hotkeyHandle, SIGNAL(activated()),
			this, SLOT(showNotesForm()));
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

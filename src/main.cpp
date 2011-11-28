#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QDebug>
#include <QTextCodec>

#include "settings/settingsmanager.h"
#include "settings/settingsdialog.h"
#include "qst/qstdbconnection.h"
#include "qst/qstabstractmodelhandler.h"
#include "qst/querygeneration/querybuilders/sqlite/sqlitebuilder.h"
#include "handlers/taghandler.h"


using namespace Qst;

void createTables();
void createPredefinedRows();
bool checkIsFirstRun(SettingsManager *sm);
SettingsMap firstRunSettings();

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.addLibraryPath(a.applicationDirPath() + "/plugins");
	QApplication::setQuitOnLastWindowClosed(false);

	SqLiteBuilder builder;
	QstAbstractModelHandler::setQueryBuilder(&builder);
	QTextCodec *pTextCodec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForTr(pTextCodec);

	SettingsManager sm = SettingsManager("GAS Soft", "WhiteLightNotes");
	SettingsMap settings;
	if (checkIsFirstRun(&sm))
	{
		settings = firstRunSettings();
		settings[S_IS_FIRST_RUN] = false;
		sm.saveSettings(settings);
	}
	else
		settings = sm.settings();

	QstDBConnection conn;
	conn.setDriverName("QSQLITE");
	conn.setDatabaseName(settings[S_DATABASE_FILE_NAME].toString());
	conn.open();

	createTables();
	createPredefinedRows();

	MainWindow w;
	w.setSettings(settings);
	w.loadAll();
	w.showTrayIcon();
	return a.exec();
}

void createTables()
{
	Qst::QstAbstractModelHandler::evalQuery("CREATE TABLE IF NOT EXISTS tag  (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, priority INTEGER)");
	Qst::QstAbstractModelHandler::evalQuery("CREATE TABLE IF NOT EXISTS note (id INTEGER PRIMARY KEY AUTOINCREMENT, title TEXT, html_text TEXT, simple_text TEXT, date TEXT, theme TEXT, complex_data TEXT)");
	Qst::QstAbstractModelHandler::evalQuery("CREATE TABLE IF NOT EXISTS tagged_note (id INTEGER PRIMARY KEY AUTOINCREMENT, tag_id INTEGER, note_id INTEGER)");
}

void createPredefinedRows()
{
	TagHandler::createTag("All", 0);
	TagHandler::createTag("Untagged", 1);
}

bool checkIsFirstRun(SettingsManager *sm)
{
	return sm->value(S_IS_FIRST_RUN, QVariant(true)).toBool();
}

SettingsMap firstRunSettings()
{
	SettingsDialog dlg;
	dlg.setSettings(SettingsDialog::defaultSettings());
	dlg.showWelcomeString();
	dlg.exec();
	return dlg.settings();
}

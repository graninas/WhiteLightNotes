#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QDebug>
#include <QTextCodec>

#include "settings/settingsmanager.h"

#include "qst/qstdbconnection.h"
#include "qst/querygeneration/querybuilders/sqlite/sqlitebuilder.h"

#include "qst/qstabstractmodelhandler.h"

#include "handlers/taghandler.h"

using namespace Qst;

void createTables();
void createPredefinedRows();

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.addLibraryPath(a.applicationDirPath() + "/plugins");	// Задается путь к папке с плагинами.

	QTextCodec *pTextCodec = QTextCodec::codecForName("UTF-8");
	Q_ASSERT_X(pTextCodec != NULL, "codecPointer", "Invalid Codec");
	QTextCodec::setCodecForTr(pTextCodec);

	SettingsManager sm = SettingsManager("GAS Soft", "WhiteLightNotes");
	QString dbFilePath = sm.value("Database.FilePath",
								  QApplication::applicationDirPath()).toString();

	SqLiteBuilder builder;
	QstAbstractModelHandler::setQueryBuilder(&builder);

	QstDBConnection conn;
	conn.setDriverName("QSQLITE");
	conn.setDatabaseName(dbFilePath + "/WhiteLightNotes.db");
	conn.open();

	createTables();
	createPredefinedRows();

	MainWindow w;
	w.loadAll();
//	w.show();
	w.showTrayIcon();
	QApplication::setQuitOnLastWindowClosed(false);
	return a.exec();
}

void createTables()
{
	Qst::QstAbstractModelHandler::evalQuery("CREATE TABLE IF NOT EXISTS tag  (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, priority INTEGER)");
	Qst::QstAbstractModelHandler::evalQuery("CREATE TABLE IF NOT EXISTS note (id INTEGER PRIMARY KEY AUTOINCREMENT, title TEXT, html_text TEXT, simple_text TEXT, date TEXT, complex_data TEXT)");
	Qst::QstAbstractModelHandler::evalQuery("CREATE TABLE IF NOT EXISTS tagged_note (id INTEGER PRIMARY KEY AUTOINCREMENT, tag_id INTEGER, note_id INTEGER)");
}

void createPredefinedRows()
{
	TagHandler::createTag("All", 0);
	TagHandler::createTag("Untagged", 1);
}

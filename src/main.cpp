#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QDebug>
#include <QTextCodec>

#include "settings/settingsmanager.h"

#include "qst/qstdbconnection.h"
#include "qst/querygeneration/querybuilders/sqlite/sqlitebuilder.h"

#include "qst/qstabstractmodelhandler.h"

using namespace Qst;

void createTables();

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

	MainWindow w;
	w.loadAll();
	w.show();
	w.showTrayIcon();
//	QApplication::setQuitOnLastWindowClosed(false);
	return a.exec();
}

void createTables()
{
	Qst::QstAbstractModelHandler::evalQuery("CREATE TABLE IF NOT EXISTS tag (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
}

#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QDebug>
#include <QTextCodec>

#include "settings/settingsmanager.h"

#include "qst/qstdbconnection.h"
#include "qst/querygeneration/querybuilders/sqlite/sqlitebuilder.h"

using namespace Qst;

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

	MainWindow w;
	w.show();
	w.showTrayIcon();
//	QApplication::setQuitOnLastWindowClosed(false);
    return a.exec();
}

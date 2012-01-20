/****************************************************************************
** WhiteLight Notes 0.9 rc1
** Copyright (C)  Granin A.S. 2011
** 
**
** This file is part of the WhiteLight Notes project.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3 included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/licenses/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** authors.
**
** Author: Granin, Alexandr
** graninas@gmail.com
****************************************************************************/

#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QTextCodec>

#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "settings/settingsmanager.h"
#include "settings/settingsdialog.h"
#include "qst/qstdbconnection.h"
#include "qst/qstabstractmodelhandler.h"
#include "qst/querygeneration/querybuilders/sqlite/sqlitebuilder.h"
#include "handlers/taghandler.h"


#undef FILE_LOG

using namespace Qst;

SettingsMap preRun();
void createTables();
void createPredefinedRows();
bool checkIsFirstRun(SettingsManager *sm);
SettingsMap firstRunSettings();
void customMessageHandler(QtMsgType type, const char *msg);

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.addLibraryPath(a.applicationDirPath() + "/plugins");
	QApplication::setQuitOnLastWindowClosed(false);

#ifdef FILE_LOG
	qInstallMsgHandler(customMessageHandler);
#endif

	SqLiteBuilder builder;
	QstAbstractModelHandler::setQueryBuilder(&builder);
	QTextCodec *pTextCodec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForTr(pTextCodec);

	SettingsMap settings = preRun();
	if (settings.isEmpty())
		return 0;

	createTables();
	createPredefinedRows();

	MainWindow w;
	w.setSettings(settings);
	w.loadAll();
	w.showTrayIcon();
	return a.exec();
}

SettingsMap preRun()
{
	SettingsManager sm = SettingsManager("GAS Soft", "WhiteLightNotes");
	SettingsMap settings;
	QstDBConnection conn;
	conn.setDriverName("QSQLITE");

	if (checkIsFirstRun(&sm))
	{
		settings = firstRunSettings();
		if (settings.isEmpty())
			return SettingsMap();
	}
	else
		settings = sm.settings();

	bool repeat = true;
	while (repeat)
	{
		conn.setDatabaseName(settings[S_DATABASE_FILE_NAME].toString());
		if (!conn.open())
		{
			QMessageBox msgBox;
			msgBox.setText(QMessageBox::tr("DB file does not found or it has invalid format.\n\n(")
						   + settings[S_DATABASE_FILE_NAME].toString() + ").");
			msgBox.setInformativeText(QMessageBox::tr("Please, select another DB file name and path."));
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.setIcon(QMessageBox::Critical);
			msgBox.exec();
			repeat = true;

			SettingsDialog dlg;
			dlg.setSettings(settings);
			dlg.showWelcomeString();
			if (dlg.exec() == QDialog::Accepted)
				settings = dlg.settings();
			else return SettingsMap();
		}
		else repeat = false;
	}
	settings[S_IS_FIRST_RUN] = false;
	sm.saveSettings(settings);
	return settings;
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
	if (dlg.exec() == QDialog::Accepted)
		return dlg.settings();
	return SettingsMap();
}

void customMessageHandler(QtMsgType type, const char *msg)
{
	QString txt;
	switch (type) {
	case QtDebugMsg:    txt = QString("\nDebug: %1").arg(msg);    break;
	case QtWarningMsg:  txt = QString("\nWarning: %1").arg(msg);  break;
	case QtCriticalMsg: txt = QString("\nCritical: %1").arg(msg); break;
	case QtFatalMsg:    txt = QString("\nFatal: %1").arg(msg);    break;
	}

	QFile outFile(QApplication::applicationDirPath() +  "/debuglog.txt");
	outFile.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream ts(&outFile);
	ts << txt << endl;
}

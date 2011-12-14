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

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QApplication>
#include <QFileDialog>

#include "notetheme.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
	ui->l_WelcomeString->hide();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

SettingsMap SettingsDialog::settings() const
{
	SettingsMap map;
	map[S_DEFAULT_COLOR_THEME]    = _defaultColorTheme();
	map[S_DATABASE_FILE_NAME]     = ui->le_DatabaseFile->text();
	map[S_CHANGE_FONT_SIZE_STEP]  = ui->sb_ChangeFontSizeStep->value();
	map[S_NEW_NOTE_TEXT_TEMPLATE] = ui->le_NewNoteTextTemplate->text();
	map[S_NOTE_SHOWING_TEMPLATE]  = ui->le_NoteShowingTemplate->text();
	return map;
}

void SettingsDialog::setSettings(const SettingsMap &settings)
{
	_setColorThemeSettings(settings);
	ui->le_DatabaseFile->setText(settings[S_DATABASE_FILE_NAME].toString());
	ui->sb_ChangeFontSizeStep->setValue(settings[S_CHANGE_FONT_SIZE_STEP].toInt());
	ui->le_NewNoteTextTemplate->setText(settings[S_NEW_NOTE_TEXT_TEMPLATE].toString());
	ui->le_NoteShowingTemplate->setText(settings[S_NOTE_SHOWING_TEMPLATE].toString());
}

void SettingsDialog::showWelcomeString()
{
	ui->l_WelcomeString->show();
}

SettingsMap SettingsDialog::defaultSettings()
{
	QString appDirPath = QApplication::applicationDirPath();
	SettingsMap map;
	map[S_DATABASE_FILE_NAME]     = appDirPath + "/" + DEFAULT_DATABASE_FILE_NAME;
	map[S_CHANGE_FONT_SIZE_STEP]  = 10;
	map[S_DEFAULT_COLOR_THEME]    = "red";
	map[S_NEW_NOTE_TEXT_TEMPLATE] = appDirPath + "/resources/NewNoteTextTemplate.html";
	map[S_NOTE_SHOWING_TEMPLATE]  = appDirPath + "/resources/NoteShowingTemplate.html";

	return map;
}

void SettingsDialog::selectDatabaseFile()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		 tr("Open file"), "/", tr("SQLite DB Files (*.db);;All files (*.*)"));

	if (!fileName.isEmpty())
		ui->le_DatabaseFile->setText(fileName);
}

void SettingsDialog::selectNewNoteTextTemplate()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		 tr("Open file"), "/", tr("HTML files (*.htm, *.html);;All files (*.*)"));

	if (!fileName.isEmpty())
		ui->le_NewNoteTextTemplate->setText(fileName);
}

void SettingsDialog::selectNoteShowingTemplate()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		 tr("Open file"), "/", tr("HTML files (*.htm, *.html);;All files (*.*)"));

	if (!fileName.isEmpty())
		ui->le_NoteShowingTemplate->setText(fileName);
}

QStringList SettingsDialog::_capitalize(const QStringList &list) const
{
	QStringList res;
	foreach (QString str, list)
		res.append(str[0].toUpper() + str.mid(1));
	return res;
}

QString SettingsDialog::_defaultColorTheme() const
{
	QString colTxt = ui->cb_DefaultColorTheme->currentText();
	return colTxt[0].toLower() + colTxt.mid(1);
}

void SettingsDialog::_setColorThemeSettings(const SettingsMap &settings)
{
	NoteTheme theme;
	ui->cb_DefaultColorTheme->addItems(_capitalize(theme.supportedColorThemes()));
	QString defColorTheme = settings[S_DEFAULT_COLOR_THEME].toString();
	int indexOfTheme = theme.supportedColorThemes().indexOf(defColorTheme);
	if (indexOfTheme != -1) ui->cb_DefaultColorTheme->setCurrentIndex(indexOfTheme);
	else                    ui->cb_DefaultColorTheme->setCurrentIndex(0);
}

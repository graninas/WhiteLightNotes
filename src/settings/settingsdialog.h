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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

#include "settings.h"

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

	SettingsMap settings() const;
	void setSettings(const SettingsMap &settings);

	void showWelcomeString();

	static SettingsMap defaultSettings();

public slots:

	void selectDatabaseFile();
	void selectNewNoteTextTemplate();
	void selectNoteShowingTemplate();

private:
    Ui::SettingsDialog *ui;

	QStringList _capitalize(const QStringList &list) const;
	QString _defaultColorTheme() const;
	void _setColorThemeSettings(const SettingsMap &settings);
	void _setDefaultFilteringBy(const SettingsMap &settings);
};

#endif // SETTINGSDIALOG_H

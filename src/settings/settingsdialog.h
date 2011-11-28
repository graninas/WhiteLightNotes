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
};

#endif // SETTINGSDIALOG_H

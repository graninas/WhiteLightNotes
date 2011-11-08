#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QSettings>

class SettingsManager
{
public:
	SettingsManager(const QString &organization,
					const QString &application);
	~SettingsManager();

	void setValue (const QString &key, const QVariant &value);
    QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;

private:

	QSettings *_settings;
};

#endif // SETTINGSMANAGER_H

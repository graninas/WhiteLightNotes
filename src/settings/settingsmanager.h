#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QSettings>
#include "settings/settings.h"

class SettingsManager
{
public:
	SettingsManager(const QString &organization,
					const QString &application);
	~SettingsManager();

	void setValue (const QString &key, const QVariant &value);
    QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;

	SettingsMap settings() const;
	void saveSettings(const SettingsMap &settings);

private:

	QSettings *_settings;
};

#endif // SETTINGSMANAGER_H

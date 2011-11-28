#include "settingsmanager.h"

#include <QStringList>

SettingsManager::SettingsManager(const QString &organization,
								 const QString &application)
{
	_settings = new QSettings(QSettings::IniFormat,
							  QSettings::UserScope,
							  organization,
							  application);
}

SettingsManager::~SettingsManager()
{
	Q_ASSERT(_settings != NULL);
	delete _settings;
}

void SettingsManager::setValue(const QString &key,
							   const QVariant &value)
{
	_settings->setValue(key, value);
}

QVariant SettingsManager::value(const QString &key,
								const QVariant &defaultValue) const
{
	return _settings->value(key, defaultValue);
}

SettingsMap SettingsManager::settings() const
{
	QStringList keys = _settings->allKeys();
	SettingsMap map;
	foreach (QString key, keys)
		map.insert(key, _settings->value(key));
	return map;
}

void SettingsManager::saveSettings(const SettingsMap &settingsMap)
{
	QStringList keys = settingsMap.keys();
	foreach (QString key, keys)
		_settings->setValue(key, settingsMap.value(key));
	_settings->sync();
}

#include "settingsmanager.h"

#include <QStringList>

SettingsManager::SettingsManager(const QString &organization,
								 const QString &application)
{
	_settings = new QSettings(organization, application);
}

SettingsManager::~SettingsManager()
{
	Q_ASSERT(_settings != NULL);
	delete _settings;
}

void SettingsManager::setValue(const QString &key,
							   const QVariant &value)
{
    QStringList SectionKey;
    SectionKey << key.split(QChar('.'));

	_settings->beginGroup(SectionKey[0]);
	_settings->setValue(SectionKey[1], value);
	_settings->endGroup();
}

QVariant SettingsManager::value(const QString &key, const QVariant &defaultValue) const
{
    QStringList SectionKey;
    SectionKey << key.split(QChar('.'));

	QVariant returnValue;
	_settings->beginGroup(SectionKey[0]);
	returnValue = _settings->value(SectionKey[1], defaultValue);
	_settings->endGroup();
    return returnValue;
}

/****************************************************************************
** WhiteLight Notes 0.9 rc2
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

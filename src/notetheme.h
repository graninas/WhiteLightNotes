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

#ifndef NOTETHEME_H
#define NOTETHEME_H

#include <QMap>
#include <QPair>
#include <QString>
#include <QStringList>

class NoteTheme
{
public:

	typedef QMap<QString, QString> ThemeColorsMap;
	typedef QMap<QString, QString> ColorOfThemeMap;

public:
	NoteTheme();

	ThemeColorsMap themeColorsMap() const;

	QStringList supportedTokens() const;
	QStringList supportedColorThemes() const;

	QString colorize(const QString &htmlTemplate,
					 const QStringList &tokens,
					 const QString &oldThemeName,
					 const QString &newThemeName,
					 const bool &newSelectState,
					 const bool &oldSelectState) const;

	QString colorize(const QString &htmlTemplate,
					 const QStringList &tokens,
					 const QString &oldThemeName,
					 const QString &newThemeName) const;

	QString getThemePrefix(const QString &html) const;

private:

	ThemeColorsMap  _themeColorsMap;
	QStringList     _supportedThemes;
	QStringList     _supportedTokens;

	// For current theme recognition in delegate - until no other ways to do this.
	// First ocurence of color (title background) is color of theme.
	ColorOfThemeMap _colorOfThemeMap;

	void _addUndefinedColorsMap();
	void _addRedThemeColorsMap();
	void _addBlueThemeColorsMap();
	void _addOrangeThemeColorsMap();
};

#endif // NOTETHEME_H

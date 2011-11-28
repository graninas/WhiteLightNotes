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

#include "notetheme.h"

#include <QDebug>

NoteTheme::NoteTheme()
{
	_addUndefinedColorsMap();
	_addRedThemeColorsMap();
	_addBlueThemeColorsMap();
	_addOrangeThemeColorsMap();

	_supportedTokens << "title.background"
					 << "title.text"
					 << "datetime.background"
					 << "datetime.text"
					 << "note.background"
					 << "note.text"
					 << "tags.background"
					 << "tags.text";
}

NoteTheme::ThemeColorsMap NoteTheme::themeColorsMap() const
{
	return _themeColorsMap;
}

QStringList NoteTheme::supportedTokens() const
{
	return _supportedTokens;
}

QStringList NoteTheme::supportedColorThemes() const
{
	return _supportedThemes;
}

QString NoteTheme::colorize(const QString &htmlTemplate,
							const QStringList &tokens,
							const QString &oldThemeName,
							const QString &newThemeName,
							const bool &newSelectState,
							const bool &oldSelectState) const
{
	Q_ASSERT(!_themeColorsMap.isEmpty());

	QString oldSel = "";
	QString newSel = "";
	if (oldSelectState) oldSel = "selected.";
	if (newSelectState) newSel = "selected.";

	QString res = htmlTemplate;
	foreach (QString token, tokens)
	{
		QString oldKey = oldThemeName + "." + oldSel + token;
		QString newKey = newThemeName + "." + newSel + token;

		QString before = _themeColorsMap.value(oldKey);
		QString after  = _themeColorsMap.value(newKey);

		res.replace(before, after);
	}
	return res;
}

QString NoteTheme::colorize(const QString &htmlTemplate,
							const QStringList &tokens,
							const QString &oldThemeName,
							const QString &newThemeName) const
{
	return colorize(htmlTemplate, tokens, oldThemeName,
					newThemeName, false, false);
}

QString NoteTheme::getThemePrefix(const QString &html) const
{
	ColorOfThemeMap::const_iterator iter = _colorOfThemeMap.begin();
	while (iter != _colorOfThemeMap.end())
	{
		if (html.contains(iter.key()))
			return iter.value();
		iter++;
	}
	return QString();
}

void NoteTheme::_addUndefinedColorsMap()
{
	_supportedThemes << "undefined";
	_colorOfThemeMap.insert("%title.background%", "undefined.selected");
	_colorOfThemeMap.insert("%title.background%", "undefined");
	_themeColorsMap.insert("undefined.selected.title.background",    "%title.background%");
	_themeColorsMap.insert("undefined.selected.title.text",          "%title.text%");
	_themeColorsMap.insert("undefined.selected.datetime.background", "%datetime.background%");
	_themeColorsMap.insert("undefined.selected.datetime.text",       "%datetime.text%");
	_themeColorsMap.insert("undefined.selected.note.background",     "%note.background%");
	_themeColorsMap.insert("undefined.selected.note.text",           "");
	_themeColorsMap.insert("undefined.selected.tags.background",     "%tags.background%");
	_themeColorsMap.insert("undefined.selected.tags.text",           "%tags.text%");

	_themeColorsMap.insert("undefined.title.background",    "%title.background%");
	_themeColorsMap.insert("undefined.title.text",          "%title.text%");
	_themeColorsMap.insert("undefined.datetime.background", "%datetime.background%");
	_themeColorsMap.insert("undefined.datetime.text",       "%datetime.text%");
	_themeColorsMap.insert("undefined.note.background",     "%note.background%");
	_themeColorsMap.insert("undefined.note.text",           "");
	_themeColorsMap.insert("undefined.tags.background",     "%tags.background%");
	_themeColorsMap.insert("undefined.tags.text",           "%tags.text%");
}

void NoteTheme::_addRedThemeColorsMap()
{
	_supportedThemes << "red";
	_colorOfThemeMap.insert("#fed3ce", "red.selected");
	_colorOfThemeMap.insert("#fef5f4", "red");
	_themeColorsMap.insert("red.selected.title.background",    "#fed3ce");
	_themeColorsMap.insert("red.selected.title.text",          "#905048");
	_themeColorsMap.insert("red.selected.datetime.background", "#fed3cd");
	_themeColorsMap.insert("red.selected.datetime.text",       "#9b5d56");
	_themeColorsMap.insert("red.selected.note.background",     "#ffffff");
	_themeColorsMap.insert("red.selected.note.text",           "");
	_themeColorsMap.insert("red.selected.tags.background",     "#fffffe");
	_themeColorsMap.insert("red.selected.tags.text",           "#a28a88");

	_themeColorsMap.insert("red.title.background",    "#fef5f4");
	_themeColorsMap.insert("red.title.text",          "#8c6d6a");
	_themeColorsMap.insert("red.datetime.background", "#fef5f5");
	_themeColorsMap.insert("red.datetime.text",       "#886966");
	_themeColorsMap.insert("red.note.background",     "#ffffff");
	_themeColorsMap.insert("red.note.text",           "");
	_themeColorsMap.insert("red.tags.background",     "#fffffe");
	_themeColorsMap.insert("red.tags.text",           "#a28a88");
}

void NoteTheme::_addBlueThemeColorsMap()
{
	_supportedThemes << "blue";
	_colorOfThemeMap.insert("#cedffc", "blue.selected");
	_colorOfThemeMap.insert("#f4f8fe", "blue");
	_themeColorsMap.insert("blue.selected.title.background",    "#cedffc");
	_themeColorsMap.insert("blue.selected.title.text",          "#48618c");
	_themeColorsMap.insert("blue.selected.datetime.background", "#cedffd");
	_themeColorsMap.insert("blue.selected.datetime.text",       "#566d97");
	_themeColorsMap.insert("blue.selected.note.background",     "#ffffff");
	_themeColorsMap.insert("blue.selected.note.text",           "");
	_themeColorsMap.insert("blue.selected.tags.background",     "#fffffe");
	_themeColorsMap.insert("blue.selected.tags.text",           "#8891a1");

	_themeColorsMap.insert("blue.title.background",    "#f4f8fe");
	_themeColorsMap.insert("blue.title.text",          "#556279");
	_themeColorsMap.insert("blue.datetime.background", "#f4f8ff");
	_themeColorsMap.insert("blue.datetime.text",       "#667186");
	_themeColorsMap.insert("blue.note.background",     "#ffffff");
	_themeColorsMap.insert("blue.note.text",           "");
	_themeColorsMap.insert("blue.tags.background",     "#fffffe");
	_themeColorsMap.insert("blue.tags.text",           "#8891a1");
}

void NoteTheme::_addOrangeThemeColorsMap()
{
	_supportedThemes << "orange";
	_colorOfThemeMap.insert("#fee1ce", "orange.selected");
	_colorOfThemeMap.insert("#fef8f4", "orange");
	_themeColorsMap.insert("orange.selected.title.background",    "#fee1ce");
	_themeColorsMap.insert("orange.selected.title.text",          "#906448");
	_themeColorsMap.insert("orange.selected.datetime.background", "#fee1cf");
	_themeColorsMap.insert("orange.selected.datetime.text",       "#9b7156");
	_themeColorsMap.insert("orange.selected.note.background",     "#ffffff");
	_themeColorsMap.insert("orange.selected.note.text",           "");
	_themeColorsMap.insert("orange.selected.tags.background",     "#fffffe");
	_themeColorsMap.insert("orange.selected.tags.text",           "#a29288");

	_themeColorsMap.insert("orange.title.background",    "#fef8f4");
	_themeColorsMap.insert("orange.title.text",          "#7b6455");
	_themeColorsMap.insert("orange.datetime.background", "#fef8f5");
	_themeColorsMap.insert("orange.datetime.text",       "#887366");
	_themeColorsMap.insert("orange.note.background",     "#ffffff");
	_themeColorsMap.insert("orange.note.text",           "");
	_themeColorsMap.insert("orange.tags.background",     "#fffffe");
	_themeColorsMap.insert("orange.tags.text",           "#a29288");
}

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

#include "note.h"

#include "notetheme.h"
#include "qst/qstglobal.h"

#include <QDebug>

Note::Note()
	:
	  _theme("undefined")
{
	clearTags();
}

Note::Note(QVariant noteID,
		   QString title,
		   QString simpleText,
		   QString htmlText,
		   QDateTime date,
		   QString complexText,
		   QString theme,
		   QStringList tagList)
	:
	  _noteID(noteID),
	  _title(title),
	  _simpleText(simpleText),
	  _htmlText(htmlText),
	  _date(date),
	  _complexText(complexText),
	  _theme(theme),
	  _tagList(tagList)
{

}

QVariant Note::noteID() const
{
	return _noteID;
}

QString Note::title() const
{
	return _title;
}

QString Note::simpleText() const
{
	return _simpleText;
}

QString Note::htmlText() const
{
	return _htmlText;
}

QDateTime Note::date() const
{
	return _date;
}

QString Note::complexText() const
{
	return _complexText;
}

QString Note::theme() const
{
	return _theme;
}

void Note::setTitle(const QString &title)
{
	_title = title;
}

void Note::setDate(const QDateTime &date)
{
	_date = date;
}

void Note::appendTag(const QString &tag)
{
	QString t = tag.simplified();
	if (t == "All" || t == "Untagged")
		return;

	if (!_tagList.contains(t))
	{
		_tagList.append(t);
		_tagList.removeAll("Untagged");
	}
}

void Note::removeTag(const QString &tag)
{
	QString t = tag.simplified();
	if (t == "All" || t == "Untagged")
		return;

	_tagList.removeAll(t);

	if (_tagList.count() == 1)
	{
		Q_ASSERT(_tagList.first() == "All");
		_tagList.append("Untagged");
	}
}

void Note::removeDuplicateTags()
{
	_tagList.removeDuplicates();
}

void Note::clearTags()
{
	_tagList.clear();
	_tagList.append("All");
	_tagList.append("Untagged");
}

QStringList Note::tagList() const
{
	return _tagList;
}

QString Note::tags(bool includeAllTag, bool includeUntaggedTag) const
{
	QStringList l = _tagList;
	if (!includeAllTag)      l.removeAll("All");
	if (!includeUntaggedTag) l.removeAll("Untagged");

	QString res;
	for (int i = 0; i < l.count(); ++i)
	{
		if (i == 0) res = l[i];
		else        res += ", " + l[i];
	}
	return res;
}

void Note::create(const QString &title,
				  const QString &plainText,
				  const QString &htmlText,
				  const QDateTime &date,
				  const QString &noteShowingTemplate)
{
	_title = title;
	_simpleText = plainText;
	_htmlText = htmlText;
	_date = date;
	_theme = "blue";
	QString onlyHtmlText = _cutHtmlHeaders(htmlText);
	QString strDateTime  = date.toString(Qst::DEFAULT_DATE_TIME_FORMAT);
	NoteTheme noteTheme;
	_complexText = noteTheme.colorize(noteShowingTemplate,
									  noteTheme.supportedTokens(),
									  "undefined",  _theme,
									  false, false);
	_complexText.replace("%title%",    title);
	_complexText.replace("%datetime%", strDateTime);
	_complexText.replace("%note%",     onlyHtmlText);
	_complexText.replace("%tags%",     tags(true, true));
}

void Note::update(const QString &title,
				  const QString &plainText,
				  const QString &htmlText,
				  const QDateTime &date,
				  const QString &noteShowingTemplate)
{
	_title = title;
	_simpleText = plainText;
	_htmlText = htmlText;
	_date = date;
	QString onlyHtmlText = _cutHtmlHeaders(htmlText);
	QString strDateTime  = date.toString(Qst::DEFAULT_DATE_TIME_FORMAT);
	NoteTheme noteTheme;
	_complexText = noteTheme.colorize(noteShowingTemplate,
									  noteTheme.supportedTokens(),
									  "undefined", _theme,
									  false, false);
	_complexText.replace("%title%",    title);
	_complexText.replace("%datetime%", strDateTime);
	_complexText.replace("%note%",     onlyHtmlText);
	_complexText.replace("%tags%",     tags(true, true));
}

void Note::changeColorTheme(const QString &newTheme)
{
	NoteTheme noteTheme;
	_complexText = noteTheme.colorize(_complexText,
									  noteTheme.supportedTokens(),
									  _theme, newTheme,
									  false, false);
	_theme = newTheme;
}

bool Note::isValid() const
{
	qDebug() << _simpleText << _tagList << _date << _complexText;
	return !_simpleText.isEmpty() &&
		   !_tagList.isEmpty() &&
		   _date.isValid() &&
		   !_complexText.isEmpty();
}

QString Note::_cutHtmlHeaders(const QString &htmlStr) const
{
	QString res = htmlStr;
	int idx = res.indexOf("<body");
	while(res[idx] != QChar('>'))
		idx++;
	res.remove(0, idx+1);
	return res.left(res.length() - QString("</body></html>").length());
}

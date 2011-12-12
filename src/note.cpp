#include "note.h"

#include "notetheme.h"
#include "qst/qstglobal.h"

Note::Note()
	:
	  _theme("undefined")
{
	clearTags();
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

void Note::create(const QString title,
				  const QString &plainText,
				  const QString &htmlText,
				  const QDateTime &date,
				  const QString &noteShowingTemplate)
{
	QString onlyHtmlText = _cutHtmlHeaders(htmlText);
	QString strDateTime  = _date.toString(Qst::DEFAULT_DATE_TIME_FORMAT);
	QString newTheme     = (_theme == "undefined") ? "blue" : _theme;
	NoteTheme noteTheme;
	_complexText = noteTheme.colorize(noteShowingTemplate,
									  noteTheme.supportedTokens(),
									  _theme,
									  newTheme,
									  false,
									  false);
	_complexText.replace("%title%",    _title);
	_complexText.replace("%datetime%", strDateTime);
	_complexText.replace("%note%",     onlyHtmlText);
	_complexText.replace("%tags%",     tags(true, true));
	_title = title;
	_simpleText = plainText;
	_htmlText = htmlText;
	_date = date;
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

bool Note::isValid() const
{
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
	return res.left(res.length() - QString("</body></html>").length());;
}

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

#ifndef NOTE_H
#define NOTE_H

#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QVariant>

class Note
{
private:

	QVariant _noteID;

	QString _title;
	QString _simpleText;
	QString _htmlText;
	QDateTime   _date;
	QString     _complexText;
	QString     _theme;
	QStringList _tagList;

public:
    Note();
	Note(QVariant noteID,
		 QString title,
		 QString simpleText,
		 QString htmlText,
		 QDateTime date,
		 QString complexText,
		 QString theme,
		 QStringList tagList);

	QVariant noteID() const;

	QString   title()       const;
	QString   simpleText()  const;
	QString   htmlText()    const;
	QDateTime date()        const;
	QString   complexText() const;
	QString   theme()       const;

	void setTitle(const QString &title);
	void setDate(const QDateTime &date);

	void appendTag(const QString &tag);
	void removeTag(const QString &tag);
	void removeDuplicateTags();
	void clearTags();
	QStringList tagList() const;
	QString tags(bool includeAllTag, bool includeUntaggedTag) const;

	void create(const QString &title,
				const QString &plainText,
				const QString &htmlText,
				const QDateTime &date,
				const QString &noteShowingTemplate);
	void update(const QString &title,
				const QString &plainText,
				const QString &htmlText,
				const QDateTime &date,
				const QString &noteShowingTemplate);

	void changeColorTheme(const QString &newTheme);

	bool isValid() const;

private:

	QString _cutHtmlHeaders(const QString &htmlStr) const;
};

#endif // NOTE_H

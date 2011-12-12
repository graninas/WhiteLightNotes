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
	QStringList _tagList;
	QString     _theme;

public:
    Note();

	QVariant noteID() const;

	QString   title()       const;
	QString   simpleText()  const;
	QString   htmlText()    const;
	QDateTime date()        const;
	QString   complexText() const;
	QString   theme()       const;

	void setTitle(const QString &title);
	void create(const QString title,
				const QString &plainText,
				const QString &htmlText,
				const QDateTime &date,
				const QString &noteShowingTemplate);
	void setDate(const QDateTime &date);

	void appendTag(const QString &tag);
	void removeTag(const QString &tag);
	void removeDuplicateTags();
	void clearTags();
	QStringList tagList() const;
	QString tags(bool includeAllTag, bool includeUntaggedTag) const;

	bool isValid() const;

private:

	QString _cutHtmlHeaders(const QString &htmlStr) const;
};

#endif // NOTE_H

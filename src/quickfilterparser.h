#ifndef QUICKFILTERPARSER_H
#define QUICKFILTERPARSER_H

#include <QMap>
#include <QString>
#include <QStringList>

typedef QMap<QString, QStringList> StringListMap;

class QuickFilterParser
{
public:
    QuickFilterParser();

	static StringListMap parse(const QString &filterString,
							   const QString &defaultSpecificator);
};

#endif // QUICKFILTERPARSER_H

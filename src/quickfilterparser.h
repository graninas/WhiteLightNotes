#ifndef QUICKFILTERPARSER_H
#define QUICKFILTERPARSER_H

#include <QMap>
#include <QString>
#include <QStringList>

#include "statemachine/statemachine.h"

class QuickFilterParser
{
public:
    QuickFilterParser();

	static StringListMap parse(const QString &filterString,
							   const QString &defaultSpecificator);
};

#endif // QUICKFILTERPARSER_H

/****************************************************************************
** QST 0.6.2 alpha
** Copyright (C) 2011 Granin A.S.
** Contact: Granin A.S. (graninas@gmail.com)
**
** This file is part of the Qst module of the QsT SQL Tools.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: http://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3 included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/licenses/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** author (graninas@gmail.com).
**
****************************************************************************/

#include "qstdefaultitemnameextractor.h"

#include <QRegExp>
#include <QStringList>

namespace Qst
{

/*!
  \class QstDefaultItemNameExtractor
  \brief
\lang_Russian
	Класс позволяет извлекать фактическое имя поля из строковой константы,
	например, "price" из "count(price)".
	Класс используется в QstBatch, если не передан другой экстрактор.

	Поддерживаются следующие выражения:
\endlang

\lang_English
	Default class for item name extraction. For example, extracted item name
	of field name "count(price)" is "price", extracted item name of field name
	"count([key]) AS id" is "id" (not "key"!), etc.

	These expressions are supported:
\endlang

\verbatim
Srting                      Extracted name
""                          "id"
"id"                        "id"
"[id]"                      "id"
"([id])"                    "id"
"[(id)]"                    "id"
"count(id)"                 "id"
"key as id"                 "id"
"key AS id"                 "id"
"count(key) AS id"          "id"
"count([key]) AS id"        "id"
"max(id)"                   "id"
"min(id)"                   "id"
"sum(id)"                   "id"
"FieldName alias"           "alias"
"count(key) alias"          "alias"
"FieldName [alias]"         "alias"
"count(key)  [alias]"       "alias"
\endverbatim
*/

/*!
\lang_Russian
	Конструктор по умолчанию.
\endlang

\lang_English
	Default constructor.
\endlang
*/
QstDefaultItemNameExtractor::QstDefaultItemNameExtractor()
	:
	_str(QString())
{
}

/*!
\lang_Russian
	Конструктор, принимающий строковую константу, содержащую имя для извлечения.
\endlang

\lang_English
	Constructor taked string constant with name for item name extracting.
\endlang
*/

QstDefaultItemNameExtractor::QstDefaultItemNameExtractor(const QString &str)
	:
	_str(str)
{
}

QstDefaultItemNameExtractor::~QstDefaultItemNameExtractor()
{
}

/*!
\lang_Russian
	Ивзлекает из сохраненной ранее строковой константы фактическое имя поля.
\endlang

\lang_English
	Extracts factual item name from previously loaded string.
\endlang
*/
QString QstDefaultItemNameExtractor::extract() const
{
	return extract(_str);
}

/*!
\lang_Russian
	Извлекает из переданной строковой константы фактическое имя поля.
\endlang

\lang_English
	Extracts factual item name from string.
\endlang
*/
QString QstDefaultItemNameExtractor::extract(const QString &str) const
{
	if (str.isEmpty())
		return QString();

	QStringList splitted = str.split(" ", QString::SkipEmptyParts);
	QString		resString = splitted[splitted.count()-1];

	int pos = resString.indexOf( QString(" as "), 0, Qt::CaseInsensitive );

	if (pos != -1)
		return _getFromBrackets(resString.mid(4 + pos)); // 4 == SQL_AS_KEYWORD.lenght() + 2
	else
		return _getFromBrackets(resString);

return resString;
}


QString QstDefaultItemNameExtractor::_getFromBrackets(const QString &str) const
{
	int startPos = str.indexOf("(");
	int endPos = str.indexOf(")");

	if (startPos != -1 && endPos != -1 && (endPos - startPos)>1)
	{
		return _getFromBrackets(str.mid(startPos + 1, endPos - startPos - 1));
	}

	startPos = str.indexOf("[");
	endPos = str.indexOf("]");

	if (startPos != -1 && endPos != -1 && (endPos - startPos)>1)
	{
		return _getFromBrackets(str.mid(startPos + 1, endPos - startPos - 1));
	}

	return str;
}

}

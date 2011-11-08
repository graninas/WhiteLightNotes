#ifndef SQLITEFORMAT_H
#define SQLITEFORMAT_H

#include <QString>

const QString SQL_INSERT        = "INSERT INTO";
const QString SQL_UPDATE        = "UPDATE";
const QString SQL_DELETE        = "DELETE FROM";
const QString SQL_VALUES        = "VALUES";
const QString SQL_SET           = "SET";
const QString SQL_ORDER_BY      = "ORDER BY";
const QString SQL_GROUP_BY      = "GROUP BY";
const QString SQL_HAVING        = "HAVING";
const QString SQL_EXECUTE       = "SELECT";
const QString SQL_SELECT        = "SELECT";
const QString SQL_FROM          = "FROM";
const QString SQL_WHERE         = "WHERE";
const QString SQL_ON            = "ON";
const QString SQL_LEFT_JOIN     = "LEFT JOIN";
const QString SQL_INNER_JOIN    = "INNER JOIN";
const QString SQL_RIGHT_JOIN    = "RIGHT JOIN";
const QString SQL_FULL_JOIN     = "FULL JOIN";
const QString SQL_PARAMETERS    = "";
const QString SQL_AS_RETURN_VALUE = "";


const QString TO_STRING_CONVERT = QString("(CAST (%1 as TEXT)");
const QString TO_DATE_CONVERT   = QString("to_date(%1, %2)");

const QString DATE_FORMAT = "dd.MM.yyyy";
const QString TIME_FORMAT = "hh:mm:ss";
const QString DATE_TIME_FORMAT = "dd.MM.yyyy hh:mm:ss";

#endif // SQLITEFORMAT_H

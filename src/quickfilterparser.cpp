#include "quickfilterparser.h"

#include "statemachine/transtable.h"

typedef Transition T;

TransTable table()
{
	QString t = "t";
	QString n = "n";
	QString b = "b";
	QString c = "c";
	QString lett = "_0123456789абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯabefghijklmopqrsuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	QString colon = ":";
	QString space = " ";
	QString pipe  = "|";
	QString quote = "\"";
	QString symb = "!\\\"#$%&'()*+,-./\n\r;<=>?@[]^`{}~";

	State q1("Empty");
	State q2("Token");
	State q3("Filter");
	State q4("EndOfFilterItem");
	State q5("FullFilter");

	TransTable table;
	table << q1 << q2 << q3 << q4 << q5;
	table << Event(t)     << T(C, q2) << T(C, q3) << T(C, q3) << T(N, q4) << T(C, q5)
		  << Event(n)     << T(C, q2) << T(C, q3) << T(C, q3) << T(N, q4) << T(C, q5)
		  << Event(b)     << T(C, q2) << T(C, q3) << T(C, q3) << T(N, q4) << T(C, q5)
		  << Event(c)     << T(C, q2) << T(C, q3) << T(C, q3) << T(N, q4) << T(C, q5)
		  << Event(lett)  << T(C, q3) << T(C, q3) << T(C, q3) << T(N, q4) << T(C, q5)
		  << Event(colon) << T(N, q1) << T(S, q3) << T(F, q4) << T(N, q4) << T(C, q5)
		  << Event(space) << T(N, q1) << T(F, q4) << T(F, q4) << T(N, q4) << T(C, q5)
		  << Event(pipe)  << T(N, q1) << T(F, q1) << T(F, q1) << T(N, q1) << T(C, q5)
		  << Event(quote) << T(N, q5) << T(F, q4) << T(F, q4) << T(N, q4) << T(F, q4)
		  << Event(symb)  << T(N, q1) << T(F, q4) << T(F, q4) << T(N, q4) << T(C, q5)
		;
	return table;
}



QuickFilterParser::QuickFilterParser()
{
}

StringListMap QuickFilterParser::parse(const QString &filterString,
									   const QString &defaultSpecificator)
{
	StateMachine sm;
	sm.setTransTable(table());
	sm.set
}




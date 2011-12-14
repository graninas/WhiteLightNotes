#include "quickfilterparser.h"

#include "statemachine/transtable.h"

#include <QDebug>

typedef Transition T;

TransTable table()
{
	QString t = "t";
	QString n = "n";
	QString b = "b";
	QString c = "c";
	QString lett = "_0123456789абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯadefghijklmopqrsuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	QString colon = ":";
	QString space = " ";
	QString pipe  = "|";
	QString quote = "\"";
	QString symb = "!\\\"#$%&'()*+,-./;<=>?@[]^`{}~";
	QString eot = "\n\r";

	State q1("Empty");
	State q2("Token");
	State q3("Filter");
	State q4("EndOfFilterItem");
	State q5("FullFilter");
	State q6("WaitFilterSkipNonLetters");

	TransTable table;
	table << q1 << q2 << q3 << q4 << q5 << q6;
	table << Event(t)     << T(C, q2) << T(C, q3) << T(C, q3) << T(N, q4) << T(C, q5) << T(C, q3)
		  << Event(n)     << T(C, q2) << T(C, q3) << T(C, q3) << T(N, q4) << T(C, q5) << T(C, q3)
		  << Event(b)     << T(C, q2) << T(C, q3) << T(C, q3) << T(N, q4) << T(C, q5) << T(C, q3)
		  << Event(c)     << T(C, q2) << T(C, q3) << T(C, q3) << T(N, q4) << T(C, q5) << T(C, q3)
		  << Event(lett)  << T(C, q3) << T(C, q3) << T(C, q3) << T(N, q4) << T(C, q5) << T(C, q3)
		  << Event(colon) << T(N, q1) << T(S, q6) << T(F, q4) << T(N, q4) << T(C, q5) << T(N, q6)
		  << Event(space) << T(N, q1) << T(F, q4) << T(F, q4) << T(N, q4) << T(C, q5) << T(N, q6)
		  << Event(pipe)  << T(N, q1) << T(F, q1) << T(F, q1) << T(N, q1) << T(C, q5) << T(A, q1)
		  << Event(quote) << T(N, q5) << T(F, q4) << T(F, q4) << T(N, q4) << T(F, q4) << T(N, q5)
		  << Event(symb)  << T(N, q1) << T(F, q4) << T(F, q4) << T(N, q4) << T(C, q5) << T(N, q6)
		  << Event(eot)   << T(N, q1) << T(F, q1) << T(F, q1) << T(N, q1) << T(F, q1) << T(N, q1)
		;
	return table;
}



QuickFilterParser::QuickFilterParser()
{
}

StringListMap QuickFilterParser::parse(const QString &filterString,
									   const QString &defaultSpecificator)
{
	StateMachine sm = StateMachine(table(), State("Empty"), "t:");

	QString s1 = "tag1 w3534| t:   tag2 j;j035908 | \"fsd %f\" | n:note";
	StringListMap m1 = sm.process(s1);
	StringListMap testM1;
	testM1["t:"].append("tag1");
	testM1["t:"].append("tag2");
	testM1["t:"].append("fsd %f");
	testM1["n:"].append("note");

	qDebug() << m1;

	Q_ASSERT(m1 == testM1);

	return StringListMap();
}




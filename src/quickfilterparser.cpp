/****************************************************************************
** WhiteLight Notes 0.9 rc1
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

#include "quickfilterparser.h"

#include "statemachine/transtable.h"

typedef Transition T;

TransTable table()
{
	QString t = "t";
	QString n = "n";
	QString d = "d";
	QString c = "c";
	QString lett = "_0123456789абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯabefghijklmopqrsuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
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
		  << Event(d)     << T(C, q2) << T(C, q3) << T(C, q3) << T(N, q4) << T(C, q5) << T(C, q3)
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
	StateMachine sm = StateMachine(table());

	QString s1 = "tag1 w3534| t:   tag2 j;j035908 | \"fsd %f\" | n:note";
	StringListMap m1 = sm.process(s1, State("Empty"), "t:");
	StringListMap testM1;
	testM1["t:"].append("tag1");
	testM1["t:"].append("tag2");
	testM1["t:"].append("fsd %f");
	testM1["n:"].append("note");
	Q_ASSERT(m1 == testM1);

	QString s2 = "d: \"10.10.10\"| n:\"Samantha Carther\"   | t:   tag1 | and_More";
	StringListMap m2 = sm.process(s2, State("Empty"), "n:");
	StringListMap testM2;
	testM2["d:"].append("10.10.10");
	testM2["n:"].append("Samantha Carther");
	testM2["n:"].append("and_More");
	testM2["t:"].append("tag1");
	Q_ASSERT(m2 == testM2);

	return sm.process(filterString, State("Empty"), defaultSpecificator);
}




#include "quickfilterparser.h"

QuickFilterParser::QuickFilterParser()
{
}

StringListMap QuickFilterParser::parse(const QString &filterString) const
{
	// Parsing fails if t: or n: or b: defined without |.
	StringListMap map;
	if (filterString.contains("|"))
	{
		QStringList l = filterString.split("|", QString::SkipEmptyParts);

		foreach (QString s, l)
		{
			QString simple = s.simplified();
			QString prefix = simple.left(2);
			QString filter = simple.right(simple.length() - 2).simplified();

			if (prefix == "n:" || prefix == "t:" || prefix == "d:")
			{
				if (!filter.isEmpty()) map[prefix].append(filter);
			}
			else if (!simple.isEmpty()) map["n:"].append(simple);
		}
	}
	else
		if (!filterString.isEmpty())
			map["n:"].append(filterString.simplified());
	return map;
}

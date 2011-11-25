#ifndef TAGSMODEL_H
#define TAGSMODEL_H

#include "qst/mvc/qstplainquerymodel.h"

class TagsModel : public Qst::QstPlainQueryModel
{
public:
    TagsModel();

	void setTagSelectable(const QString &tag, const bool &selectable);
	void setTagColumnIndex(const int &columnIndex);

	Qt::ItemFlags flags ( const QModelIndex & index ) const;
	QVariant data(const QModelIndex &item, int role) const;

private:

	typedef QMap<QString, bool> SelectableTagMap;

	SelectableTagMap _selectableTagMap;
	int _tagColumnIndex;
};

#endif // TAGSMODEL_H

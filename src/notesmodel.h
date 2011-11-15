#ifndef NOTESMODEL_H
#define NOTESMODEL_H

#include "qst/mvc/qstplainquerymodel.h"

class NotesModel : public Qst::QstPlainQueryModel
{
public:
    NotesModel();

	virtual bool setData(const QModelIndex &index,
						 const QVariant &value,
						 int role);

	virtual Qt::ItemFlags flags ( const QModelIndex & index ) const;
};

#endif // NOTESMODEL_H

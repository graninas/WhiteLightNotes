#include "notesmodel.h"

NotesModel::NotesModel()
{
}

bool NotesModel::NotesModel::setData(const QModelIndex &index,
									 const QVariant &value,
									 int role)
{
	return true;
}

Qt::ItemFlags NotesModel::flags ( const QModelIndex & index ) const
{
	return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

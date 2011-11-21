#include "notesmodel.h"

NotesModel::NotesModel()
{
}

Qt::ItemFlags NotesModel::flags ( const QModelIndex & index ) const
{
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

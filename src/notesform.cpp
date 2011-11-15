#include "notesform.h"
#include "ui_notesform.h"

#include "noteitemdelegate.h"

#include <QTextEdit>

#include <QDebug>

using namespace Qst;

NotesForm::NotesForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NotesForm)
{
    ui->setupUi(this);

	_tagHandler.setQuery(tagBatch());
	_tagHandler.setModel(&_tagModel);
	_tagHandler.setListView(ui->lv_Tags);

	_noteHandler.setQuery(noteBatch());
	_noteHandler.setModel(&_noteModel);
	_noteHandler.setTableView(ui->tv_Notes);
}

NotesForm::~NotesForm()
{
    delete ui;
}

void NotesForm::loadAll()
{
	loadTags();
	loadNotes();
}

void NotesForm::loadTags()
{
	_tagHandler.reload();

	QObject::connect(ui->lv_Tags->selectionModel(),
					 SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
					 this, SLOT(loadNotes()));
}

void NotesForm::loadNotes()
{
	_noteHandler.updatePlaceholder("selected_tags", _tagHandler.viewSelectedKeys());
	_noteHandler.updatePlaceholder("simple_text", QstValue(ui->le_QuickFilter->text(),
														   Qst::Like,
														   Qst::LeftRightPercents));
	_noteHandler.reload();
}

Qst::QstVariantListMap NotesForm::_getFilters(const QString &filterString)
{
	Qst::QstVariantListMap map;
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

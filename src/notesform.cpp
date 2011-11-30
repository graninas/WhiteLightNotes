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

	ui->tv_Notes->setItemDelegate(&_noteItemDelegate);

	_tagHandler.setListView(ui->lv_Tags);
	_tagHandler.setViewSorting(ui->lv_Tags, true);
	_tagHandler.setModel(&_tagModel);
	_tagHandler.reload();

	_noteHandler.setQuery(noteBatch());
	_noteHandler.setModel(&_noteModel);
	_noteHandler.setListView(ui->tv_Notes);
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
	_setFilteringQuery();
	_tagHandler.reload();

	QObject::connect(ui->lv_Tags->selectionModel(),
					 SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
					 this, SLOT(loadNotes()));
}

void NotesForm::loadNotes()
{
	_noteHandler.updatePlaceholder("selected_tags", _tagHandler.viewSelectedKeys());
	_noteHandler.reload();
}

void NotesForm::reset()
{
	ui->le_QuickFilter->clear();
	ui->le_QuickFilter->setFocus();
}

StringListMap NotesForm::_getFilters(const QString &filterString)
{
	StringListMap map;
	QStringList splited = filterString.split(" ", QString::SkipEmptyParts);
	foreach(QString tag, splited)
		map["t:"].append(tag.simplified());
	return map;
}

void NotesForm::_setFilteringQuery()
{
	StringListMap listMap = _getFilters(ui->le_QuickFilter->text());
	if (!listMap.contains("t:") || listMap["t:"].isEmpty())
	{
		_tagHandler.setQuery(tagBatch());
		return;
	}
	_tagHandler.setQuery(linkedTagsBatch(listMap["t:"]));
}


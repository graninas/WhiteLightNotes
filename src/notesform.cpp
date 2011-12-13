#include "notesform.h"
#include "ui_notesform.h"

#include <QTextEdit>
#include <QDebug>

#include "noteitemdelegate.h"
#include "handlers/taggednotehandler.h"

using namespace Qst;

NotesForm::NotesForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NotesForm)
{
    ui->setupUi(this);

	ui->tv_Notes->setItemDelegate(&_noteItemDelegate);

	_tagHandler.setListView(ui->lv_Tags);
	_tagHandler.setViewSorting(ui->lv_Tags, false);
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

void NotesForm::editNote()
{
	if (_noteHandler.viewKeyValue().isNull())
		return;
	QVariantMap vals = _noteHandler.viewFieldsValueMap();
	Q_ASSERT(!vals["id"].isNull());
	Note n = Note(vals["id"],
				  vals["title"].toString(),
				  vals["simple_text"].toString(),
				  vals["html_text"].toString(),
				  QDateTime::fromString(vals["date"].toString(), Qst::DEFAULT_DATE_TIME_FORMAT),
				  vals["complex_data"].toString(),
				  vals["theme"].toString(),
				  TaggedNoteHandler::tagList(vals["id"]));
	emit editNote(n);
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


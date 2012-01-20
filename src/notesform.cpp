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

#include "notesform.h"
#include "ui_notesform.h"

#include <QTextEdit>
#include <QDebug>

#include "noteitemdelegate.h"
#include "handlers/taggednotehandler.h"
#include "quickfilterparser.h"

using namespace Qst;

NotesForm::NotesForm(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::NotesForm),
	_defaultSpecificator("t:")
{
    ui->setupUi(this);

	ui->tv_Notes->setItemDelegate(&_noteItemDelegate);

	_tagHandler.setListView(ui->lv_Tags);
	_tagHandler.setViewSorting(ui->lv_Tags, false);
	_tagHandler.setModel(&_tagModel);
	_tagHandler.reload();

	_noteHandler.setModel(&_noteModel);
	_noteHandler.setListView(ui->tv_Notes);

	QObject::connect(ui->action_BlueTheme,   SIGNAL(triggered()), this, SLOT(setBlueColorTheme()));
	QObject::connect(ui->action_RedTheme,    SIGNAL(triggered()), this, SLOT(setRedColorTheme()));
	QObject::connect(ui->action_OrangeTheme, SIGNAL(triggered()), this, SLOT(setOrangeColorTheme()));
	QObject::connect(ui->le_QuickFilter,     SIGNAL(textChanged(QString)), this, SLOT(loadAll()));
}

NotesForm::~NotesForm()
{
    delete ui;
}

void NotesForm::setSettings(const SettingsMap &settings)
{
	if (settings[S_DEFAULT_FILTERING_BY].toString() == "Tags")
		_defaultSpecificator = "t:";
	else if (settings[S_DEFAULT_FILTERING_BY].toString() == "Note text")
		_defaultSpecificator = "n:";
	else if (settings[S_DEFAULT_FILTERING_BY].toString() == "Datetime")
		_defaultSpecificator = "d:";
	else
	{
		qDebug() << settings;
		Q_ASSERT(false);
	}
}

void NotesForm::loadAll()
{
	_quickFilterItems = QuickFilterParser::parse(ui->le_QuickFilter->text(), _defaultSpecificator);
	loadTags ();
	loadNotes();
}

void NotesForm::loadTags()
{
	QStringList filters = _quickFilterItems["t:"];
	filters.append(_selectedNoteTags);
	filters.removeDuplicates();
	if (filters.isEmpty())
		_tagHandler.setQuery(tagBatch());
	else
		_tagHandler.setQuery(linkedTagsBatch(filters));

	_tagHandler.reload();
	QObject::connect(ui->lv_Tags->selectionModel(),
					 SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
					 this, SLOT(loadNotes()));
}

void NotesForm::loadNotes()
{
	_noteHandler.setQuery(noteBatch(_quickFilterItems));
	_noteHandler.updatePlaceholder("selected_tags", _tagHandler.viewSelectedKeys());
	_noteHandler.reload();

	QObject::connect(ui->tv_Notes->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
					 this, SLOT(_saveNoteTagsInQuickFilter(QItemSelection,QItemSelection)));
}

void NotesForm::createNote()
{
	emit newNote();
}

void NotesForm::editNote()
{
	if (_noteHandler.viewKeyValue().isNull())
		return;
	QVariantMap vals = _noteHandler.viewFieldsValueMap();
	Q_ASSERT(!vals["id"].isNull());
	emit editNote(_note(vals));
}

void NotesForm::setRedColorTheme()
{
	if (_noteHandler.viewKeyValue().isNull())
		return;
	QVariantMap vals = _noteHandler.viewFieldsValueMap();
	Q_ASSERT(!vals["id"].isNull());
	emit changeColorTheme(_note(vals), "red");
}

void NotesForm::setBlueColorTheme()
{
	if (_noteHandler.viewKeyValue().isNull())
		return;
	QVariantMap vals = _noteHandler.viewFieldsValueMap();
	Q_ASSERT(!vals["id"].isNull());
	emit changeColorTheme(_note(vals), "blue");
}

void NotesForm::setOrangeColorTheme()
{
	if (_noteHandler.viewKeyValue().isNull())
		return;
	QVariantMap vals = _noteHandler.viewFieldsValueMap();
	Q_ASSERT(!vals["id"].isNull());
	emit changeColorTheme(_note(vals), "orange");
}

void NotesForm::showAllTags()
{
	_selectedNoteTags.clear();
	loadTags();
}

Note NotesForm::_note(const QVariantMap &vals) const
{
	return Note(vals["id"],
				vals["title"].toString(),
				vals["simple_text"].toString(),
				vals["html_text"].toString(),
				QDateTime::fromString(vals["date"].toString(), Qst::DEFAULT_DATE_TIME_FORMAT),
				vals["complex_data"].toString(),
				vals["theme"].toString(),
				TaggedNoteHandler::tagList(vals["id"]));
}

void NotesForm::_saveNoteTagsInQuickFilter(const QItemSelection &selected,
										   const QItemSelection &deselected)
{
	Q_UNUSED(deselected);
	if (selected.indexes().isEmpty())
		return;

	_selectedNoteTags.clear();
	QStringList ids;
	foreach (QModelIndex idx, selected.indexes())
		ids.append(_noteHandler.fieldValue("id", idx).toString());
	ids.removeDuplicates();
	foreach (QString id, ids)
	{
		QStringList tagList = TaggedNoteHandler::tagList(id.toInt());
		_selectedNoteTags.append(tagList);
	}
	loadTags();
}

#include "notesform.h"
#include "ui_notesform.h"

NotesForm::NotesForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NotesForm)
{
    ui->setupUi(this);

	_tagHandler.setQuery(tagBatch());
	_tagHandler.setModel(&_tagModel);
	_tagHandler.setListView(ui->lv_TagsList);

	_noteHandler.setQuery(noteBatch());
	_noteHandler.setModel(&_noteModel);
	_noteHandler.setListView(ui->lv_NotesList);
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

	QObject::connect(ui->lv_TagsList->selectionModel(),
					 SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
					 this, SLOT(loadNotes()));
}

void NotesForm::loadNotes()
{
	_noteHandler.updatePlaceholder("selected_tags",
								   _tagHandler.viewSelectedKeys());
	_noteHandler.reload();
}

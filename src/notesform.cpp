#include "notesform.h"
#include "ui_notesform.h"

NotesForm::NotesForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NotesForm)
{
    ui->setupUi(this);

	_tagHandler.setQuery(tagBatch());
	_tagHandler.setModel(&_tagModel);
	_tagHandler.setListView(ui->lv_tagsList);

	_noteHandler.setQuery(noteBatch());
	_noteHandler.setModel(&_noteModel);
	_noteHandler.setListView(ui->lw_NotesFormList);
}

NotesForm::~NotesForm()
{
    delete ui;
}

void NotesForm::loadAll()
{
	loadTags();
	loadNotesForm();
}

void NotesForm::loadTags()
{
	_tagHandler.reload();
}

void NotesForm::loadNotesForm()
{

}

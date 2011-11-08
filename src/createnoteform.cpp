#include "createnoteform.h"
#include "ui_createnoteform.h"

#include <QUrl>
#include <QFont>

#include <QDebug>
#include <QString>
#include <QDateTime>

#include "handlers/notehandler.h"
#include "handlers/tagednotehandler.h"
#include "handlers/taghandler.h"

CreateNoteForm::CreateNoteForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateNoteForm)
{
    ui->setupUi(this);

	ui->te_NoteHtmlText->setUndoRedoEnabled(true);
}

CreateNoteForm::~CreateNoteForm()
{
    delete ui;
}

void CreateNoteForm::resetEditFields()
{
	// TODO
}

void CreateNoteForm::adjustButtons(const QTextCharFormat &format)
{
	if (format.fontWeight() > static_cast<int>(QFont::Normal)) ui->actionBold->setChecked(true);
	else ui->actionBold->setChecked(false);

	if (format.fontItalic()) ui->actionItalic->setChecked(true);
	else ui->actionItalic->setChecked(false);

	if (format.fontUnderline()) ui->actionUnderline->setChecked(true);
	else ui->actionUnderline->setChecked(false);
}

void CreateNoteForm::setBold(bool bold)
{
	if (bold) ui->te_NoteHtmlText->setFontWeight(QFont::Bold);
	else      ui->te_NoteHtmlText->setFontWeight(QFont::Normal);
}

void CreateNoteForm::finishCreation()
{
	QString note = ui->te_NoteHtmlText->toHtml();
	QVariant noteID = NoteHandler::createNote(note, QDateTime::currentDateTime());
	Q_ASSERT(!noteID.isNull());

	// Возможно, сделать обновление тегов записи через INSERT OR REPLACE,
	// а не через удаление / добавление.
	TagedNoteHandler tnh;
	tnh.deleteTagedNotes(noteID);

	Qst::QstPlainQueryModel thModel;
	TagHandler th;
	th.setQuery(tagedNoteBatch());
	th.setModel(&thModel);

	QStringList tagsList = ui->le_Tags->text().split(',');
	foreach (QString tag, tagsList)
	{
		th.updatePlaceholder("name", tag);
		th.reload();
		QVariant tagID = th.fieldValue("id");
		if (tagID.isNull())
			tagID = th.createTag(tag);

		tnh.createTagedNote(tagID, noteID);
	}
}

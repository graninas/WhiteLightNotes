#include "createnoteform.h"
#include "ui_createnoteform.h"

#include <QFont>

#include <QString>
#include <QDateTime>

#include <QDebug>

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

void CreateNoteForm::setNoteTemplate(const QString &noteTemplate)
{
	_noteTemplate = noteTemplate;
}

void CreateNoteForm::resetEditFields()
{
	ui->te_NoteHtmlText->setHtml(_noteTemplate);
	qDebug() << _noteTemplate;
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
	_createNote();
	emit noteCreated();
	this->close();
}

void CreateNoteForm::finishAndNew()
{
	_createNote();
	emit noteCreated();
	resetEditFields();
	ui->te_NoteHtmlText->setFocus();
}

void CreateNoteForm::_createNote()
{
	QString note = ui->te_NoteHtmlText->toHtml();
	QVariant noteID = NoteHandler::createNote(note, QDateTime::currentDateTime());
	Q_ASSERT(!noteID.isNull());

	// Возможно, сделать обновление тегов записи через INSERT OR REPLACE,
	// а не через удаление / добавление.
	TagedNoteHandler::deleteTagedNotes(noteID);

	QStringList tagsList = ui->le_Tags->text().split(',', QString::SkipEmptyParts);

	if (tagsList.isEmpty())
		tagsList << QString("untaged");

	foreach (QString tag, tagsList)
		TagedNoteHandler::createTagedNote(_createTag(tag), noteID);
}

QVariant CreateNoteForm::_createTag(const QString &tagName)
{
	Qst::QstPlainQueryModel model;
	TagHandler th;
	th.setQuery(tagBatch());
	th.setModel(&model);
	th.updatePlaceholder("name", tagName);
	th.reload();
	QVariant tagID = th.fieldValue("id");

	if (tagID.isNull()) return TagHandler::createTag(tagName);
	return tagID;
}

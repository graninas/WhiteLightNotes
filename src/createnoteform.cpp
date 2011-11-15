#include "createnoteform.h"
#include "ui_createnoteform.h"

#include <QFont>

#include <QString>
#include <QDateTime>
#include <QMenu>

#include <QDebug>

#include "handlers/notehandler.h"
#include "handlers/taggednotehandler.h"
#include "handlers/taghandler.h"

CreateNoteForm::CreateNoteForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateNoteForm)
{
    ui->setupUi(this);

	ui->te_NoteHtmlText->setUndoRedoEnabled(true);

	_okEnterShortcut.setShortcut (QKeySequence(Qt::CTRL + Qt::Key_Enter));
	_okReturnShortcut.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Return));
	_okAndNewEnterShortcut.setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Return));
	_okAndNewReturnShortcut.setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Enter));
	_cancelShortcut.setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_Escape));

	connect(&_okEnterShortcut, SIGNAL(activated()), this, SLOT(finishCreation()));
	connect(&_okReturnShortcut, SIGNAL(activated()), this, SLOT(finishCreation()));
	connect(&_okAndNewEnterShortcut, SIGNAL(activated()), this, SLOT(finishAndNew()));
	connect(&_okAndNewReturnShortcut, SIGNAL(activated()), this, SLOT(finishCreation()));
	connect(&_cancelShortcut, SIGNAL(activated()), this, SLOT(cancelCreation()));
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
	_setShortcutsEnabled(true);
	ui->te_NoteHtmlText->setFocus();
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
	_setShortcutsEnabled(false);
	_createNote();
	emit noteCreated();
	this->close();
}

void CreateNoteForm::finishAndNew()
{
	_setShortcutsEnabled(false);
	_createNote();
	emit noteCreated();
	resetEditFields();
	ui->te_NoteHtmlText->setFocus();
}

void CreateNoteForm::cancelCreation()
{
	_setShortcutsEnabled(false);
	this->close();
}

void CreateNoteForm::incFontSize()
{
	ui->te_NoteHtmlText->setFontPointSize(
				ui->te_NoteHtmlText->fontPointSize() + 10);
}

void CreateNoteForm::decFontSize()
{
	ui->te_NoteHtmlText->setFontPointSize(
				ui->te_NoteHtmlText->fontPointSize() - 10);
}

void CreateNoteForm::_createNote()
{
	QString noteHtml   = ui->te_NoteHtmlText->toHtml();
	QString noteSimple = ui->te_NoteHtmlText->toPlainText();

	QVariant noteID = NoteHandler::createNote(noteHtml,
											  noteSimple,
											  QDateTime::currentDateTime());
	Q_ASSERT(!noteID.isNull());

	// Возможно, сделать обновление тегов записи через INSERT OR REPLACE,
	// а не через удаление / добавление.
	TaggedNoteHandler::deleteTaggedNotes(noteID);

	QStringList tagsList = ui->le_Tags->text().split(',', QString::SkipEmptyParts);

	if (tagsList.isEmpty())
		tagsList << QString("Untagged");

	tagsList << "All";

	foreach (QString tag, tagsList)
	{
		if (!tag.simplified().isEmpty())
			TaggedNoteHandler::createTaggedNote(_createTag(tag.simplified()), noteID);
	}
}

QVariant CreateNoteForm::_createTag(const QString &tagName)
{
	Qst::QstBatch b = tagBatch();
	b.updatePlaceholder("name", tagName);
	QVariant tagID = TagHandler::fieldValue(b, "id");

	if (tagID.isNull()) TagHandler::createTag(tagName);

	return TagHandler::fieldValue(b, "id");
}

void CreateNoteForm::_setShortcutsEnabled(bool enabled)
{
	_okEnterShortcut.setEnabled(enabled);
	_okReturnShortcut.setEnabled(enabled);
	_okAndNewEnterShortcut.setEnabled(enabled);
	_okAndNewReturnShortcut.setEnabled(enabled);
	_cancelShortcut.setEnabled(enabled);
}

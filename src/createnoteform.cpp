#include "createnoteform.h"
#include "ui_createnoteform.h"

#include <QFont>

#include <QString>
#include <QDateTime>
#include <QMenu>

#include <QToolButton>
#include <QComboBox>

#include <QDebug>

#include "handlers/notehandler.h"
#include "handlers/taggednotehandler.h"
#include "handlers/taghandler.h"

const int FONT_SIZE_CHANGE_VALUE = 10;
const QString DEFAULT_COLOR_THEME = "red";

CreateNoteForm::CreateNoteForm(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::CreateNoteForm),
	_textColorCombobox(NULL)
{
    ui->setupUi(this);

	ui->te_NoteHtmlText->setUndoRedoEnabled(true);

	_cancelShortcut        .setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_Escape));
	_okEnterShortcut       .setShortcut(QKeySequence(Qt::CTRL  + Qt::Key_Enter));
	_okReturnShortcut      .setShortcut(QKeySequence(Qt::CTRL  + Qt::Key_Return));
	_okAndNewEnterShortcut .setShortcut(QKeySequence(Qt::CTRL  + Qt::SHIFT + Qt::Key_Return));
	_okAndNewReturnShortcut.setShortcut(QKeySequence(Qt::CTRL  + Qt::SHIFT + Qt::Key_Enter));

	connect(&_okEnterShortcut,        SIGNAL(activated()), this, SLOT(finishCreation()));
	connect(&_okReturnShortcut,       SIGNAL(activated()), this, SLOT(finishCreation()));
	connect(&_okAndNewEnterShortcut,  SIGNAL(activated()), this, SLOT(finishAndNew()));
	connect(&_okAndNewReturnShortcut, SIGNAL(activated()), this, SLOT(finishCreation()));
	connect(&_cancelShortcut,         SIGNAL(activated()), this, SLOT(cancelCreation()));

	_colorMap.insert(0,  ColorName("black",     QColor(0,0,0)));
	_colorMap.insert(1,  ColorName("blue",      QColor(0,0,255)));
	_colorMap.insert(2,  ColorName("darkgreen", QColor(0,127,0)));
	_colorMap.insert(3,  ColorName("darkgrey",  QColor(127,127,127)));
	_colorMap.insert(4,  ColorName("green",     QColor(0,255,0)));
	_colorMap.insert(5,  ColorName("lightblue", QColor(0,255,255)));
	_colorMap.insert(6,  ColorName("magenta",   QColor(255,0,255)));
	_colorMap.insert(7,  ColorName("red",       QColor(255,0,0)));
	_colorMap.insert(8,  ColorName("white",     QColor(255,255,255)));
	_colorMap.insert(9,  ColorName("yellow",    QColor(255,255,0)));
	_colorMap.insert(10, ColorName("orange",    QColor(255,127,0)));

	_textColorCombobox = new QComboBox(this);
	foreach(int key, _colorMap.keys())
	{
		ColorName cname = _colorMap[key];
		QString name = cname.first;
		QString capedName = name.at(0).toUpper() + name.mid(1);
		_textColorCombobox->addItem(QIcon(":icons/resources/edit-color-" + name + ".ico"), capedName, name);
	}
	ui->editToolBar->addWidget(_textColorCombobox);

	QObject::connect(_textColorCombobox, SIGNAL(activated(int)),
					 this, SLOT(setForegroundColor(int)));

	_tagHandler.setQuery(tagBatch());
	_tagHandler.setModel(&_tagModel);
	_tagHandler.setTableView(ui->tv_Tags);
	_tagModel.setTagColumnIndex(_tagHandler.fieldColumnIndex("info_tag"));
	_tagModel.setTagSelectable("All", false);
	_tagModel.setTagSelectable("Untagged", false);

	qDebug() <<  "\nfieldColumnIndex:" << _tagHandler.fieldColumnIndex("info_tag");
}

CreateNoteForm::~CreateNoteForm()
{
    delete ui;
}

void CreateNoteForm::setNoteTemplate(const QString &noteTemplate)
{
	_noteTemplate = noteTemplate;
}

void CreateNoteForm::setNoteTextTemplate(const QString &noteTextTemplate)
{
	_noteTextTemplate = noteTextTemplate;
}

void CreateNoteForm::setHtmlHeaderFooter(const QString &header, const QString &footer)
{
	_htmlHeader = header;
	_htmlFooter = footer;
}

void CreateNoteForm::loadTags()
{
	_tagHandler.reload();
	QObject::connect(ui->tv_Tags->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
					 this, SLOT(updateEnteredSelectedTags(QItemSelection,QItemSelection)));
}

void CreateNoteForm::reset()
{
	_setShortcutsEnabled(true);
	_enteredSelectedTags.clear();
	_enteredSelectedTags.append("All");
	_enteredSelectedTags.append("Untagged");
	_updateTagsLineEdit(_enteredSelectedTags);
	ui->te_NoteHtmlText->setHtml(_noteTextTemplate);
	ui->le_Title->setFocus();
}

void CreateNoteForm::adjustButtons(const QTextCharFormat &format)
{
	if (format.fontWeight() > static_cast<int>(QFont::Normal)) ui->actionBold->setChecked(true);
	else ui->actionBold->setChecked(false);

	if (format.fontItalic()) ui->actionItalic->setChecked(true);
	else ui->actionItalic->setChecked(false);

	if (format.fontUnderline()) ui->actionUnderline->setChecked(true);
	else ui->actionUnderline->setChecked(false);

	_adjustColorButtons(format);
}

void CreateNoteForm::setBold(bool bold)
{
	if (bold) ui->te_NoteHtmlText->setFontWeight(QFont::Bold);
	else      ui->te_NoteHtmlText->setFontWeight(QFont::Normal);
}

void CreateNoteForm::setForegroundColor(const int &colorIndex)
{
	ui->te_NoteHtmlText->setTextColor(_colorMap[colorIndex].second);
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
	reset();
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
				ui->te_NoteHtmlText->fontPointSize() + FONT_SIZE_CHANGE_VALUE);
}

void CreateNoteForm::decFontSize()
{
	ui->te_NoteHtmlText->setFontPointSize(
				ui->te_NoteHtmlText->fontPointSize() - FONT_SIZE_CHANGE_VALUE);
}

void CreateNoteForm::updateEnteredSelectedTags(const QItemSelection &selected,
											   const QItemSelection &deselected)
{
	_enteredSelectedTags.append("All");

	foreach(QModelIndex idx, selected.indexes())
	{
		QString tag = _tagHandler.fieldValue("name", idx).toString();
		Q_ASSERT(!tag.isEmpty());
		_enteredSelectedTags.append(tag);
	}

	foreach(QModelIndex idx, deselected.indexes())
		_enteredSelectedTags.removeAll(idx.data().toString());

	_enteredSelectedTags.removeDuplicates();

	if (_enteredSelectedTags.count() == 1)
		_enteredSelectedTags.append("Untagged");
	else
		_enteredSelectedTags.removeAll("Untagged");

	_updateTagsLineEdit(_enteredSelectedTags);
}

void CreateNoteForm::updateEnteredSelectedTags(const QString &changedTags)
{
	_enteredSelectedTags.append("All");

	QStringList tagList = _tagList(changedTags);

	foreach (QString tag, tagList)
		_enteredSelectedTags.append(tag);
	_enteredSelectedTags.removeDuplicates();

	if (_enteredSelectedTags.count() == 1)
		_enteredSelectedTags.append("Untagged");
	else
		_enteredSelectedTags.removeAll("Untagged");

	_updateTagsLineEdit(_enteredSelectedTags);
}

void CreateNoteForm::_createNote()
{
	updateEnteredSelectedTags(ui->le_Tags->text());
	QString noteTitle  = ui->le_Title->text();
	QString noteHtml   = ui->te_NoteHtmlText->toHtml();
	QString noteSimple = ui->te_NoteHtmlText->toPlainText();
	QDateTime dateTime = QDateTime::currentDateTime();
	QString noteComplex = _noteComplexHtml(noteTitle,
										   noteHtml,
										   dateTime,
										   _tagsText(_enteredSelectedTags));

	QVariant noteID    = NoteHandler::createNote(noteTitle,
												 noteHtml,
												 noteSimple,
												 dateTime,
												 DEFAULT_COLOR_THEME,
												 noteComplex);
	Q_ASSERT(!noteID.isNull());
	_updateTags(noteID);
}

void CreateNoteForm::_updateTags(const QVariant &noteID)
{
	// Возможно, сделать обновление тегов записи через INSERT OR REPLACE,
	// а не через удаление / добавление.
	TaggedNoteHandler::deleteTaggedNotes(noteID);
	updateEnteredSelectedTags(ui->le_Tags->text());
	TagInfoList tagInfoList = _tagInfoList(_enteredSelectedTags);

	TagInfoList::const_iterator iter = tagInfoList.begin();
	while (iter != tagInfoList.end())
	{
		QString simpleTagName = iter->first.simplified();
		if (!simpleTagName.isEmpty())
		{
			QVariant tagID = TagHandler::createTag(simpleTagName, iter->second);
			TaggedNoteHandler::createTaggedNote(tagID, noteID);
		}
		iter++;
	}
}

void CreateNoteForm::_updateTagsLineEdit(const QStringList &tags)
{
	QStringList list = tags;
	list.removeAll("All");
	list.removeAll("Untagged");
	ui->le_Tags->setText(_tagsText(list));
}

CreateNoteForm::TagInfoList CreateNoteForm::_tagInfoList(const QStringList &tagsList) const
{
	TagInfoList list;

	foreach (QString tag, tagsList)
	{
		if      (tag == "All") list.append(TagInfo(tag, 0));
		else if (tag == "Untagged") list.append(TagInfo(tag, 1));
		else list.append(TagInfo(tag, 2));
	}

	return list;
}

QStringList CreateNoteForm::_tagList(const QString &tags) const
{
	QStringList tagNamesList = tags.split(',', QString::SkipEmptyParts);

	if (tagNamesList.isEmpty())
		tagNamesList.append("Untagged");

	tagNamesList.append("All");
	QStringList resList;
	foreach (QString tag, tagNamesList)
		if (!tag.simplified().isEmpty())
			resList.append(tag.simplified());
	resList.removeDuplicates();
	return resList;
}

QString CreateNoteForm::_tagsText(const QStringList &tagsList) const
{
	QString tags;
	for (int i = 0; i < tagsList.count(); ++i)
	{
		if (i == 0) tags  = tagsList[i];
		else tags += ", " + tagsList[i];
	}

	return tags;
}

QString CreateNoteForm::_noteComplexHtml(const QString &noteTitle,
										 const QString &noteHtml,
										 const QDateTime &datetime,
										 const QString &tags) const
{
	QString onlyHtmlText = _cutHtmlHeaders(noteHtml);
	QString strDateTime = datetime.toString(Qst::DEFAULT_DATE_TIME_FORMAT);

	NoteTheme theme;
	QString res = theme.colorize(_noteTemplate,
								 theme.supportedTokens(),
								 "undefined",
								 DEFAULT_COLOR_THEME,
								 false,
								 false);

	res.replace("%title%",    noteTitle);
	res.replace("%datetime%", strDateTime);
	res.replace("%note%",     onlyHtmlText);
	res.replace("%tags%",     tags);
	return res;
}

void CreateNoteForm::_setShortcutsEnabled(bool enabled)
{
	_okEnterShortcut.setEnabled(enabled);
	_okReturnShortcut.setEnabled(enabled);
	_okAndNewEnterShortcut.setEnabled(enabled);
	_okAndNewReturnShortcut.setEnabled(enabled);
	_cancelShortcut.setEnabled(enabled);
}

QString CreateNoteForm::_cutHtmlHeaders(const QString &str) const
{
	QString res = str;
	int idx = res.indexOf("<body");
	while(res[idx] != QChar('>'))
		idx++;
	res.remove(0, idx+1);
	return res.left(res.length() - QString("</body></html>").length());;
}

void CreateNoteForm::_adjustColorButtons(const QTextCharFormat &format)
{
	QColor foregroudColor = format.foreground().color();

	foreach (int key, _colorMap.keys())
	{
		if (_colorMap[key].second == foregroudColor)
		{
			_textColorCombobox->setCurrentIndex(key);
			break;
		}
	}
}

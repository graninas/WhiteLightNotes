#ifndef CREATENOTEFORM_H
#define CREATENOTEFORM_H

#include <QMainWindow>

#include <QxtGui/qxtgui.h>
#include <QTextCharFormat>

#include <QMap>
#include <QColor>

#include "handlers/taghandler.h"
#include "tagsmodel.h"
#include "notetheme.h"

#include "settings/settings.h"

namespace Ui {
    class CreateNoteForm;
}

class CreateNoteForm : public QMainWindow
{
    Q_OBJECT

private:

	typedef int TagPriority;
	typedef QPair<QString, TagPriority> TagInfo;
	typedef QList<TagInfo> TagInfoList;

	typedef QPair<QString, QColor> ColorName;
	typedef QMap<int, ColorName> ColorMap;

public:
    explicit CreateNoteForm(QWidget *parent = 0);
    ~CreateNoteForm();

	void setNoteShowingTemplate(const QString &noteTemplate);
	void setNewNoteTextTemplate(const QString &noteTextTemplate);

	void loadTags();

	void setSettings(const SettingsMap &settings);

public slots:

	void reset();
	void adjustButtons(const QTextCharFormat &format);
	void setBold(bool bold);
	void setForegroundColor(const int &colorIndex);

	void finishCreation();
	void finishAndNew();
	void cancelCreation();

	void incFontSize();
	void decFontSize();

	void updateEnteredSelectedTags(const QItemSelection &selected,
								   const QItemSelection &deselected);
	void updateEnteredSelectedTags(const QString &changedTags);

signals:

	void noteCreated();

private:
    Ui::CreateNoteForm *ui;

	QComboBox *_textColorCombobox;

	ColorMap _colorMap;

	QString _noteShowingTemplate;
	QString _newNoteTextTemplate;

	QxtGlobalShortcut _okEnterShortcut;
	QxtGlobalShortcut _okReturnShortcut;
	QxtGlobalShortcut _okAndNewEnterShortcut;
	QxtGlobalShortcut _okAndNewReturnShortcut;
	QxtGlobalShortcut _cancelShortcut;

	TagHandler _tagHandler;
	TagsModel  _tagModel;

	QStringList _enteredSelectedTags;

	int     _changeFontSizeStep;
	QString _defaultColorTheme;

	void _createNote();
	void _updateTags(const QVariant &noteID);
	void _updateTagsLineEdit(const QStringList &tags);

	TagInfoList _tagInfoList(const QStringList &tagsList) const;
	QStringList _tagList(const QString &tags) const;
	QString     _tagsText(const QStringList &tagsList) const;

	QString _noteComplexHtml(const QString &noteTitle,
							 const QString &noteHtml,
							 const QDateTime &datetime,
							 const QString &tags) const;

	QString _cutHtmlHeaders(const QString &str) const;

	void _setShortcutsEnabled(bool enabled);
	void _adjustColorButtons(const QTextCharFormat &format);

	QString _loadFile(const QString &fileName) const;
};

#endif // CREATENOTEFORM_H

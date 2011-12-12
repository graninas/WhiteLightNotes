#ifndef EDITNOTEFORM_H
#define EDITNOTEFORM_H

#include <QMainWindow>

#include <QxtGui/qxtgui.h>
#include <QTextCharFormat>

#include <QMap>
#include <QColor>

#include "handlers/taghandler.h"
#include "tagsmodel.h"
#include "notetheme.h"

#include "note.h"

#include "settings/settings.h"

typedef int TagPriority;
typedef QPair<QString, TagPriority> TagInfo;
typedef QList<TagInfo> TagInfoList;

namespace Ui {
    class CreateNoteForm;
}

class EditNoteForm : public QMainWindow
{
    Q_OBJECT

private:

	typedef QPair<QString, QColor> ColorName;
	typedef QMap<int, ColorName>   ColorMap;

public:
	explicit EditNoteForm(QWidget *parent = 0);
	~EditNoteForm();

	void setSettings(const SettingsMap &settings);
	void setNote(const Note &note);
	void loadAll();

public slots:

	void adjustButtons(const QTextCharFormat &format);
	void setBold(bool bold);
	void setForegroundColor(const int &colorIndex);
	void incFontSize();
	void decFontSize();

	void adjustTags(QItemSelection selected, QItemSelection deselected);
	void adjustTags();

	void finish();
	void cancel();

signals:

	void finishNote(const Note &note);
	void cancelNoteEditing();

private:
    Ui::CreateNoteForm *ui;
	QComboBox *_textColorCombobox;

	QxtGlobalShortcut _okEnterShortcut;
	QxtGlobalShortcut _okReturnShortcut;
	QxtGlobalShortcut _okAndNewEnterShortcut;
	QxtGlobalShortcut _okAndNewReturnShortcut;
	QxtGlobalShortcut _cancelShortcut;

	ColorMap _colorMap;
	int      _changeFontSizeStep;
	QString  _defaultColorTheme;
	QString  _noteShowingTemplate;

	Note _note;

	TagHandler _tagHandler;
	TagsModel  _tagModel;

	QItemSelection _selectedTags;
	QItemSelection _deselectedTags;

	void _setShortcutsEnabled(bool enabled);
	void _adjustColorButtons(const QTextCharFormat &format);

	QString _loadFile(const QString &fileName) const;
};

#endif // EDITNOTEFORM_H

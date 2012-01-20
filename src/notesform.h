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

#ifndef NOTESFORM_H
#define NOTESFORM_H

#include <QMainWindow>

#include "handlers/taghandler.h"
#include "handlers/notehandler.h"

#include "noteitemdelegate.h"
#include "note.h"

#include "settings/settings.h"

namespace Ui {
    class NotesForm;
}

class NotesForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit NotesForm(QWidget *parent = 0);
    ~NotesForm();

	void setSettings(const SettingsMap &settings);

public slots:

	void loadAll();
	void loadTags();
	void loadNotes();

	void createNote();
	void editNote();

	void setRedColorTheme();
	void setBlueColorTheme();
	void setOrangeColorTheme();

	void showAllTags();

signals:

	void newNote();
	void editNote(const Note &note);
	void changeColorTheme(const Note &note, const QString &newTheme);

private:
    Ui::NotesForm *ui;

	QComboBox *_colorThemeCombobox;

	TagHandler              _tagHandler;
	Qst::QstPlainQueryModel _tagModel;

	NoteHandler             _noteHandler;
	Qst::QstPlainQueryModel _noteModel;

	NoteItemDelegate _noteItemDelegate;

	QStringList   _selectedNoteTags;
	StringListMap _quickFilterItems;
	QString       _defaultSpecificator;

	Note _note(const QVariantMap &vals) const;

private slots:

	void _saveNoteTagsInQuickFilter(const QItemSelection &selected,
									const QItemSelection &deselected);
};

#endif // NOTESFORM_H

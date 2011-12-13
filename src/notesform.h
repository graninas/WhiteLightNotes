#ifndef NOTESFORM_H
#define NOTESFORM_H

#include <QMainWindow>

#include "handlers/taghandler.h"
#include "handlers/notehandler.h"

#include "noteitemdelegate.h"
#include "note.h"

namespace Ui {
    class NotesForm;
}

class NotesForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit NotesForm(QWidget *parent = 0);
    ~NotesForm();

public slots:

	void loadAll();
	void loadTags();
	void loadNotes();

	void editNote();

	void setRedColorTheme();
	void setBlueColorTheme();
	void setOrangeColorTheme();

signals:

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

	void _setFilteringQuery();

	Note _note(const QVariantMap &vals) const;
};

#endif // NOTESFORM_H

#ifndef NOTESFORM_H
#define NOTESFORM_H

#include <QMainWindow>

#include "handlers/taghandler.h"
#include "handlers/notehandler.h"

#include "noteitemdelegate.h"
#include "quickfilterparser.h"


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
	void reset();


private:
    Ui::NotesForm *ui;

	QComboBox *_colorThemeCombobox;

	TagHandler              _tagHandler;
	Qst::QstPlainQueryModel _tagModel;

	NoteHandler             _noteHandler;
	Qst::QstPlainQueryModel _noteModel;

	NoteItemDelegate _noteItemDelegate;

	StringListMap _getFilters(const QString &filterString);
	void _setFilteringQuery();
};

#endif // NOTESFORM_H

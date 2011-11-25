#ifndef NOTESFORM_H
#define NOTESFORM_H

#include <QMainWindow>

#include "handlers/taghandler.h"
#include "handlers/notehandler.h"

#include "notesmodel.h"
#include "noteitemdelegate.h"

typedef QMap<QString, QStringList> StringListMap;

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
//	Qst::QstPlainQueryModel _noteModel;
	NotesModel  _noteModel;

	NoteItemDelegate _noteItemDelegate;

	Qst::QstVariantListMap _getFilters(const QString &filterString);
};

#endif // NOTESFORM_H

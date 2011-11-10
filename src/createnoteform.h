#ifndef CREATENOTEFORM_H
#define CREATENOTEFORM_H

#include <QMainWindow>

#include <QxtGui/qxtgui.h>
#include <QTextCharFormat>

namespace Ui {
    class CreateNoteForm;
}

class CreateNoteForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateNoteForm(QWidget *parent = 0);
    ~CreateNoteForm();

	void setNoteTemplate(const QString &noteTemplate);

public slots:

	void resetEditFields();
	void adjustButtons(const QTextCharFormat &format);
	void setBold(bool bold);

	void finishCreation();
	void finishAndNew();
	void cancelCreation();

signals:

	void noteCreated();

private:
    Ui::CreateNoteForm *ui;

	QString _noteTemplate;

	QxtGlobalShortcut _okEnterShortcut;
	QxtGlobalShortcut _okReturnShortcut;
	QxtGlobalShortcut _okAndNewEnterShortcut;
	QxtGlobalShortcut _okAndNewReturnShortcut;
	QxtGlobalShortcut _cancelShortcut;

	void _createNote();

	QVariant _createTag(const QString &tagName);

	void _setShortcutsEnabled(bool enabled);
};

#endif // CREATENOTEFORM_H

#ifndef CREATENOTEFORM_H
#define CREATENOTEFORM_H

#include <QMainWindow>
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

signals:

	void noteCreated();

private:
    Ui::CreateNoteForm *ui;

	QString _noteTemplate;

	void _createNote();

	QVariant _createTag(const QString &tagName);
};

#endif // CREATENOTEFORM_H

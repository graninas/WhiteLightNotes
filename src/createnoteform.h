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

public slots:

	void resetEditFields();
	void adjustButtons(const QTextCharFormat &format);
	void setBold(bool bold);

	void finishCreation();

private:
    Ui::CreateNoteForm *ui;
};

#endif // CREATENOTEFORM_H

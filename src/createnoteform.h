#ifndef CREATENOTEFORM_H
#define CREATENOTEFORM_H

#include <QMainWindow>

#include <QxtGui/qxtgui.h>
#include <QTextCharFormat>

#include <QMap>
#include <QColor>

namespace Ui {
    class CreateNoteForm;
}

class CreateNoteForm : public QMainWindow
{
    Q_OBJECT

private:

	typedef QPair<QString, int> TagInfo;
	typedef QList<TagInfo> TagInfoList;

	typedef QPair<QString, QColor> ColorName;
	typedef QMap<int, ColorName> ColorMap;

public:
    explicit CreateNoteForm(QWidget *parent = 0);
    ~CreateNoteForm();

	void setNoteTemplate(const QString &noteTemplate);

public slots:

	void resetEditFields();
	void adjustButtons(const QTextCharFormat &format);
	void setBold(bool bold);
	void setForegroundColor(const int &colorIndex);

	void finishCreation();
	void finishAndNew();
	void cancelCreation();

	void incFontSize();
	void decFontSize();

signals:

	void noteCreated();

private:
    Ui::CreateNoteForm *ui;

	QComboBox *_textColorCombobox;

	ColorMap _colorMap;
	QString _noteTemplate;

	QxtGlobalShortcut _okEnterShortcut;
	QxtGlobalShortcut _okReturnShortcut;
	QxtGlobalShortcut _okAndNewEnterShortcut;
	QxtGlobalShortcut _okAndNewReturnShortcut;
	QxtGlobalShortcut _cancelShortcut;

	void _createNote();

	void _setShortcutsEnabled(bool enabled);

	void _adjustColorButtons(const QTextCharFormat &format);
};

#endif // CREATENOTEFORM_H

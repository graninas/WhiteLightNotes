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

	typedef int TagPriority;
	typedef QPair<QString, TagPriority> TagInfo;
	typedef QList<TagInfo> TagInfoList;

	typedef QPair<QString, QColor> ColorName;
	typedef QMap<int, ColorName> ColorMap;

public:
    explicit CreateNoteForm(QWidget *parent = 0);
    ~CreateNoteForm();

	void setNoteTemplate(const QString &noteTemplate);
	void setNoteTextTemplate(const QString &noteTextTemplate);
	void setHtmlHeaderFooter(const QString &header, const QString &footer);

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
	QString _noteTextTemplate;
	QString _htmlHeader;
	QString _htmlFooter;

	QxtGlobalShortcut _okEnterShortcut;
	QxtGlobalShortcut _okReturnShortcut;
	QxtGlobalShortcut _okAndNewEnterShortcut;
	QxtGlobalShortcut _okAndNewReturnShortcut;
	QxtGlobalShortcut _cancelShortcut;

	void _createNote();
	void _updateTags(const QVariant &noteID);

	TagInfoList _tagInfoList();
	QString _tagsText(const TagInfoList &tagInfoList) const;

	QString _noteComplexHtml(const QString &noteTitle,
							 const QString &noteHtml,
							 const QDateTime &datetime,
							 const TagInfoList &tagInfoList) const;

//	// Due to QTBUG 22851 (https://bugreports.qt.nokia.com/browse/QTBUG-22851)
//	QString _spaceAlignedTitle(const QString &noteTitle,
//							   const QDateTime &datetime) const;

	QString _cutHtmlHeaders(const QString &str) const;

	void _setShortcutsEnabled(bool enabled);
	void _adjustColorButtons(const QTextCharFormat &format);
};

#endif // CREATENOTEFORM_H

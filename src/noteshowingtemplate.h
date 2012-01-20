#ifndef NOTESHOWINGTEMPLATE_H
#define NOTESHOWINGTEMPLATE_H

#include <QString>

QString noteShowingTemplate()
{
	QString res;
	res += "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">";
	res += "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">";
	res += "p, li { white-space: pre-wrap; }";
	res += "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">";
	res += "<table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" width=\"100%\" cellspacing=\"0\" cellpadding=\"0\">";
	res += "<tr>";
	res += "<td bgcolor=\"%title.background%\">";
	res += "<p style=\"text-align:left; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'fixedsys'; font-size:8pt; color:%title.text%;\">%title%</span></p></td>";
	res += "<td bgcolor=\"%datetime.background%\">";
	res += "<p align=\"right\" style=\"text-align:right; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'fixedsys'; font-size:8pt; color:%datetime.text%;\">%datetime%</span></p></td></tr>";
	res += "<tr>";
	res += "<td colspan=\"2\" bgcolor=\"%note.background%\">%note%</td></tr>";
	res += "<tr>";
	res += "<td colspan=\"2\" bgcolor=\"%tags.background%\"><span style=\" font-family:'fixedsys'; font-size:8pt; color:%tags.text%;\">%tags%</span></td></tr></table></body></html>";
	return res;
}

#endif // NOTESHOWINGTEMPLATE_H

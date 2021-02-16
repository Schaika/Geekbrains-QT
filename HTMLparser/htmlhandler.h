#ifndef HTMLHANDLER_H
#define HTMLHANDLER_H

#include <QObject>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QRegExp>
class HTMLhandler : public QObject
{
	Q_OBJECT
public:
	explicit HTMLhandler(QObject *parent = nullptr);
	void getHTML(const QString& searchString, const int count);
	QStringList getListOfImages() const;

private:
	void parseImages(const QString& bareHTML, const int count);
	QStringList listOfImages;
signals:

};

#endif // HTMLHANDLER_H

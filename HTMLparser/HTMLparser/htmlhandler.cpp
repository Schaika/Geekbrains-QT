#include "htmlhandler.h"


HTMLhandler::HTMLhandler(QObject *parent) : QObject(parent)
	{

	}

void HTMLhandler::getHTML(const QString& searchString, const int count)
	{
		if (searchString.isEmpty()) return;
		QNetworkAccessManager manager;
		QNetworkReply *response = manager.get(QNetworkRequest(QUrl("http://www.google.com/search?q="+searchString+"&tbm=isch")));
		QEventLoop event;
		connect(response,SIGNAL(finished()),&event,SLOT(quit()));
		event.exec();
		response->deleteLater();
		parseImages(response->readAll(),count);

	}

void HTMLhandler::parseImages(const QString& bareHTML, const int count)
	{
		listOfImages.clear();
		QRegExp regex("<img[^>]+src=\"([^\">]+)\"",Qt::CaseSensitive,QRegExp::RegExp2);
		int lastPos = 0;
		while(count+1 > listOfImages.count() && (lastPos = regex.indexIn( bareHTML, lastPos)) != -1 ) {
			lastPos += regex.matchedLength();
			listOfImages.append(regex.cap(1));

		}
		listOfImages.removeAt(0);//removes branding image
	}

QStringList HTMLhandler::getListOfImages() const
	{
		return listOfImages;
	}

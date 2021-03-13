#ifndef FRAMEWGT_H
#define FRAMEWGT_H

#include <QWidget>
#include <QGridLayout>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QUrl>
#include <QFile>
#include <QDir>
#include <QNetworkAccessManager>
#include <QNetworkReply>
class FrameWgt : public QWidget
{
	Q_OBJECT
public:
	explicit FrameWgt(const int ID=0,const QUrl& url = QString("https://www.zastavki.com/pictures/originals/2017Animals___Cats_Beautiful_British_cat_with_lilac_flowers_116288_.jpg"), QWidget *parent = nullptr);
	~FrameWgt();
private:
	QLabel* nameLabel;
	QLabel* imageLabel;
	QProgressBar* progressBar;
	QNetworkAccessManager *pnam;
	QGridLayout* layout;
	QString path;
	int myID;
private slots:
	void downloadProgress(qint64, qint64);
	void done(QNetworkReply* reply);
signals:

};

#endif // FRAMEWGT_H

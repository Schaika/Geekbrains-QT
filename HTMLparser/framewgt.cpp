#include "framewgt.h"

FrameWgt::FrameWgt(const int ID, const QUrl& url, QWidget* parent) : QWidget(parent), myID(ID)
	{
		this->setMinimumSize(250,250);
		this->setMaximumSize(250,250);
		layout = new QGridLayout(this);
		nameLabel = new QLabel("Downloading...",this);
		layout->addWidget(nameLabel,0,0,1,1);
		progressBar = new QProgressBar(this);
		layout->addWidget(progressBar,0,1,1,1);

		pnam = new QNetworkAccessManager(this);
		QNetworkRequest request(url);
		QNetworkReply* reply = pnam->get(request);
		connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(downloadProgress(qint64, qint64)));
		connect(pnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(done(QNetworkReply*)));
	}

FrameWgt::~FrameWgt()
	{
		QDir dir(QDir::currentPath()+"/tmp");
		if(dir.exists()) dir.removeRecursively();
	}

void FrameWgt::downloadProgress(qint64 received, qint64 total)
	{
		if (total <=0){
			return;
		}
		progressBar->setValue(100 * received/total);
	}

void FrameWgt::done(QNetworkReply* reply)
	{
		QDir dir(QDir::currentPath()+"/tmp");
		if (!dir.exists())
			dir.mkpath(".");
		const QByteArray &ba = reply->readAll();
		path = dir.path()+"/pic_"+QString::number(myID)+".jpg";
		QFile file(path);
		if (file.open(QIODevice::WriteOnly)){
			file.write(ba);
			file.close();
		}
		delete progressBar;
		delete nameLabel;
		imageLabel = new QLabel(this);
		QPixmap pix = QPixmap(path);
		pix = pix.scaled(this->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
		imageLabel->setPixmap(pix);
		layout->addWidget(imageLabel,0,0,3,3);
		this->setToolTip(reply->url().toString());
	}


#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include <QObject>
#include <QStandardItemModel>
#include <QThread>
#include <QApplication>
#include <QStyle>
#include <QDir>
class SearchThread : public QThread
{
	Q_OBJECT
public:
	SearchThread();
	void run() override;
	bool isActive();
	void setPath(QString);
	void whatToSearch(QString);
	void stop();
private:
	bool isInSearch;
	QString path;
	QString fileName;
signals:
	void found(QStandardItem*);
	void searchEnded();
	void updateCurrentFolder(QString);
};

#endif // SEARCHTHREAD_H

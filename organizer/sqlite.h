#ifndef SQLITE_H
#define SQLITE_H

#include "taskcontainer.h"
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QList>
#include <QSqlQueryModel>

class SQLite : public QObject
{
	Q_OBJECT
public:
	SQLite(QString dbname = "");
	QList<taskcontainer> getList();
	int getTotal();
	void removeTask(quint32 localID);
	void addTask();
	void updateTask(quint32 localID,QString text,QString date,int progress);
	static QDate parseDate(QString);
	QSqlQueryModel* getModel();
	void refreshModel();
signals:
	void updateModel(QSqlQueryModel*);
private:
	QSqlQueryModel *model=nullptr;
	bool createConnection(QString);
	void extractList();
	QList<taskcontainer>* taskList;
};

#endif // SQLITE_H

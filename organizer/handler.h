#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <QCoreApplication>
#include <QTextStream>
#include "taskcontainer.h"
#include "sqlite.h"
#include "popupwindow.h"
class handler : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int currentID READ currentID());
	Q_PROPERTY(QString currentText READ currentText());
	Q_PROPERTY(QString currentDate READ currentDate());
	Q_PROPERTY(int currentProgress READ currentProgress());
	Q_PROPERTY(bool ismarked READ mark());
	Q_PROPERTY(int taskcount READ taskCount());
	Q_PROPERTY(QString marktext READ marktext());
public:
	explicit handler(QObject *parent = nullptr);
private:
	SQLite* dbmanager;
	void validate();
	void rebuild();
	int _currentID;
	QString _currentText;
	QString _currentDate;
	int _currentProgress;
	int _currentDay;
	int _currentMonth;
	int _currentYear;
	bool _marked;
	QString _marktext;
	int _currentTasks;
	void parseDate(QString);
	QWidget *wgt = nullptr;
public:
	Q_INVOKABLE void removeTask(int ID = 0);
	Q_INVOKABLE void init();
	Q_INVOKABLE void editTask(int ID = 0, QString text = "", QString date = "", int progress = 0);
	Q_INVOKABLE void addTask();
	Q_INVOKABLE void openWindow();
	Q_INVOKABLE void closing();
	int taskCount() const;
	int currentID() const;
	QString currentText() const;
	QString currentDate() const;
	int currentProgress() const;
	bool mark() const;

	QString marktext() const;

signals:
	void appendTask();
	void removeAll();
	void updateCounter();
	void revalidate();
};

#endif // HANDLER_H

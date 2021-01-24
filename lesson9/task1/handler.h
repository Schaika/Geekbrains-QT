#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <QCoreApplication>
#include <QTextStream>
#include "taskcontainer.h"
class handler : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int currentID READ currentID())
	Q_PROPERTY(QString currentText READ currentText())
	Q_PROPERTY(QString currentDate READ currentDate())
	Q_PROPERTY(int currentProgress READ currentProgress())
public:
	explicit handler(QObject *parent = nullptr);
private:
	QList<taskcontainer> taskList = {};
	void loadFile();
	void saveToFile();
	bool process_line(QString,bool);
	void rebuild();
	int _currentID;
	QString _currentText;
	QString _currentDate;
	int _currentProgress;
	int _currentDay;
	int _currentMonth;
	int _currentYear;
	void parseDate(QString);
public:
	Q_INVOKABLE void removeTask(int ID = 0);
	Q_INVOKABLE void init();
	Q_INVOKABLE void editTask(int ID = 0, QString text = "", QString date = "", int progress = 0);
	Q_INVOKABLE void addTask();
	int currentID() const;
	QString currentText() const;
	QString currentDate() const;
	int currentProgress() const;

signals:
	void appendTask();
	void removeAll();
};

#endif // HANDLER_H

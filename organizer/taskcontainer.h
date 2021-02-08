#ifndef TASKCONTAINER_H
#define TASKCONTAINER_H
#include <QDate>

class taskcontainer
{
public:
	taskcontainer(QDate _date = QDate(1970,1,1), QString _taskText = "", quint16 _progress = 0);
	quint16 getProgress() const;
	void setProgress(const quint16& value);

	QString getTaskText() const;
	void setTaskText(const QString& value);

	QDate getDate() const;
	void setDate(const QDate& value);

	quint32 getID() const;
	void setID(const quint32& value);

	quint32 getLocalID() const;
	void setLocalID(const quint32& value);

private:
	QDate date;
	QString taskText;
	quint16 progress;
	quint32 ID;
	quint32 localID;
};

#endif // TASKCONTAINER_H

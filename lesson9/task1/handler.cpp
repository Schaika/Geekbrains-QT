#include "handler.h"
#include <QtDebug>
handler::handler(QObject *parent) : QObject(parent)
	{
	}

void handler::loadFile()
	{
		QString path = qApp->applicationDirPath();
			QString filename(path + "/tasks.txt");
			QFile file(filename);
			bool a = QFileInfo::exists(filename);
			if(a){
				if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
					return;
				QTextStream in(&file);
				bool first = true;
				while (!in.atEnd()) {
					QString line = in.readLine();
					if (!process_line(line,first)) return;
					if (!first){
						taskcontainer _temp;
						_temp.setID(_currentID);
						_temp.setTaskText(_currentText);
						_temp.setDate(QDate(_currentYear,_currentMonth,_currentDay));
						_temp.setProgress(_currentProgress);
						taskList.insert(_currentID,_temp);
					}
					first = false;
				}

			}else{
				if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
					return;
				QTextStream out(&file);
				out << "Task list:::";
				file.close();
				return;
			}
	}

void handler::saveToFile()
	{
		QString path = qApp->applicationDirPath();
			QString filename(path + "/tasks.txt");
			QFile file(filename);
			bool a = QFileInfo::exists(filename);
			if(a){
				if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
					return;
				QTextStream out(&file);
				out << "Task list:::\n";

				foreach(taskcontainer obj,taskList){
					out << "ID: '"<< obj.getID()<<"';";
					out << "text: '"<<obj.getTaskText()<<"';";
					out << "date: '"<<obj.getDate().toString("dd.MM.yyyy")<<"';";
					out << "progress: '"<<obj.getProgress()<<"';\n";
				}
				file.close();
				return;

			}
	}

bool handler::process_line(QString line,bool isfirstline)
	{
		if(isfirstline){
			if(line == QString("Task list:::")){
				return true;
			}else{
				qDebug()<< "Can't parse file";
				return false;
			}
		}
		int from,to;
		QString index = "ID: '";
		from = line.indexOf(index)+index.length();
		to = line.indexOf("';",from);
		//qDebug()<< line.midRef(from,to-from);
		_currentID = line.midRef(from,to-from).toUInt();

		index="text: '";
		from = line.indexOf(index)+index.length();
		to = line.indexOf("';",from);
		//qDebug()<< line.midRef(from,to-from);
		_currentText= line.mid(from,to-from);

		index = "date: '";
		from = line.indexOf(index)+index.length();
		to = line.indexOf("';",from);
		//qDebug()<< line.midRef(from,to-from);
		_currentDate= line.mid(from,to-from);
		parseDate(_currentDate);

		index = "progress: '";
		from = line.indexOf(index)+index.length();
		to = line.indexOf("';",from);
		//qDebug()<< line.midRef(from,to-from);
		_currentProgress= line.midRef(from,to-from).toUInt();

		return true;
	}

void handler::removeTask(int ID)
	{
		taskList.removeAt(ID);
		rebuild();
	}

void handler::init()
	{
		loadFile();
		rebuild();
	}

void handler::editTask(int ID, QString text, QString date, int progress)
	{
		taskList[ID].setTaskText(text);
		parseDate(date);
		taskList[ID].setDate(QDate(_currentYear,_currentMonth,_currentDay));
		if (progress>10) progress=10;
		if (progress<0) progress=0;
		taskList[ID].setProgress(progress);
		saveToFile();
	}

void handler::addTask()
	{
		taskcontainer _temp;
		_temp.setID(taskList.length());
		_temp.setDate(QDate::currentDate());
		taskList.append(_temp);
		rebuild();
	}
void handler::rebuild(){
		emit removeAll();
		for (int i=0;i<taskList.count();i++){
			taskList[i].setID(i);
			taskcontainer obj = taskList.at(i);
			QDate date = obj.getDate();
			_currentDate = date.toString("dd.MM.yyyy");
			_currentID = obj.getID();
			_currentText = obj.getTaskText();
			_currentProgress = obj.getProgress();
			emit appendTask();
		}
		saveToFile();
	}

void handler::parseDate(QString date)
	{
		int from,to;
		from = 0;
		to = date.indexOf(".");
		//qDebug() << date.midRef(from,to-from);
		_currentDay = date.midRef(from,to-from).toUInt();

		from = to+1;
		to = date.indexOf(".",from);
		//qDebug() << date.midRef(from,to-from);
		_currentMonth = date.midRef(from,to-from).toUInt();

		from = to+1;
		//qDebug() << date.midRef(from);
		_currentYear = date.midRef(from).toUInt();

	}

int handler::currentProgress() const
	{
		return _currentProgress;
	}

QString handler::currentDate() const
	{
		return _currentDate;
	}

QString handler::currentText() const
	{
		return _currentText;
	}

int handler::currentID() const
	{
		return _currentID;
	}

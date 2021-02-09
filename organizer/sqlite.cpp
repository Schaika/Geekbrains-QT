#include "sqlite.h"
SQLite::SQLite(QString dbname)
	{
		if(dbname.isEmpty()) return;
		if(!createConnection(dbname)) return;
	}

QList<taskcontainer> SQLite::getList()
	{
		return *taskList;
	}

int SQLite::getTotal()
	{
		return taskList->count();
	}

void SQLite::removeTask(quint32 localID)
	{
		quint32 ID = taskList->at(localID).getID();
		QString str = "DELETE FROM tasklist WHERE id=%1";
		QSqlQuery query;
		if (!query.exec(str.arg(ID))){
			//qDebug() << "Unable to delete";
		}else{
			//qDebug() << "Done!";
			extractList();
		}
	}

void SQLite::addTask()
	{
		QString str = "INSERT INTO tasklist (text, date, progress)"
					   "VALUES('%1', '%2', '%3');";
		QSqlQuery query;

		if (!query.exec(str.arg("",QDate::currentDate().toString("dd.MM.yyyy"),"0"))){
			//qDebug() << "Unable to insert";
		}else{
			//qDebug() << "Done!";
			extractList();
		}
	}

void SQLite::updateTask(quint32 localID, QString text, QString date, int progress)
	{
		quint32 ID = taskList->at(localID).getID();
		QString str = "UPDATE tasklist "
					  "SET text='%1', date='%2', progress='%3' "
					  "WHERE id=%4;";
		QSqlQuery query;
		QString strF = str.arg(text,date,QString::number(progress),QString::number(ID));
		if (!query.exec(strF)){
			//qDebug() << "Unable to update";
		}else{
			//qDebug() << "Done!";
		}
		refreshModel();
	}

void SQLite::extractList()
	{
		taskList = new QList<taskcontainer>{};
		QSqlQuery query;
		if (!query.exec("SELECT * FROM tasklist;")){
			//qDebug() << "Unable to select";
		}
		int i = 0;
		while(query.next()){

			taskcontainer _temp;
			_temp.setID(query.value(0).toUInt());
			_temp.setTaskText(query.value(1).toString());
			_temp.setDate(parseDate(query.value(2).toString()));
			_temp.setProgress(query.value(3).toUInt());
			_temp.setLocalID(i);
			taskList->insert(i,_temp);
			//qDebug() << query.value(0).toString() << " " <<
			//			query.value(1).toString() << " " <<
			//			query.value(2).toString() << " " <<
			//			query.value(3).toString();
			i++;
		}
		refreshModel();
	}

QDate SQLite::parseDate(QString dateStr)
	{
		quint16 _Day,_Month,_Year;
		int from,to;
		from = 0;
		to = dateStr.indexOf(".");
		////qDebug() << date.midRef(from,to-from);
		_Day = dateStr.midRef(from,to-from).toUInt();

		from = to+1;
		to = dateStr.indexOf(".",from);
		////qDebug() << date.midRef(from,to-from);
		_Month = dateStr.midRef(from,to-from).toUInt();

		from = to+1;
		////qDebug() << date.midRef(from);
		_Year = dateStr.midRef(from).toUInt();
		return QDate(_Year,_Month,_Day);
	}

QSqlQueryModel* SQLite::getModel()
	{
		return model;
	}

void SQLite::refreshModel()
	{
		if(model!=nullptr){
			QSqlQueryModel* _temp = model;
			model = new QSqlQueryModel;
			model->setQuery("SELECT * FROM tasklist");
			delete _temp;
		}else{
		model = new QSqlQueryModel;
		model->setQuery("SELECT * FROM tasklist");
		}
		emit updateModel(model);
	}

bool SQLite::createConnection(QString dbname)
	{
		QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
		db.setDatabaseName(dbname);
		if (!db.open()){
			//qDebug() << "Cannot open database.";
			return false;
		}
		//qDebug() << "Opened database.";

		QStringList name = db.tables();
		if (!name.contains("tasklist")){
			//qDebug() << "Table not found in database. Creating...";
			QSqlQuery query;
			QString str = "CREATE TABLE tasklist ("
							"id INTEGER NOT NULL UNIQUE,"
							"text TEXT,"
							"date TEXT,"
							"progress INTEGER,"
							"PRIMARY KEY(id AUTOINCREMENT));";
			if (!query.exec(str)){
				//qDebug() << "Unable to create table.";
			}else{
				//qDebug() << "Table created.";
			}
		}
		extractList();
		return true;
	}

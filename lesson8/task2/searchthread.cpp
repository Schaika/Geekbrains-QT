#include "searchthread.h"



SearchThread::SearchThread()
	{
		path = "";
		fileName = "";
	}

void SearchThread::run()
	{
		if (path.isEmpty() || fileName.isEmpty()) {emit searchEnded();return;}
		isInSearch = true;

		QDir dir(path);
		emit updateCurrentFolder(path);
		dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Dirs);
		QStringList dirlist = dir.entryList();
		dirlist.removeAll(".");dirlist.removeAll("..");

		dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Files);
		QStringList fileslist = dir.entryList();

		foreach(QString str,fileslist){
			if (str == fileName) {
				QStandardItem* f = new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon)), str);
				f->setToolTip(path);
				emit found(f);
			}
		}
		foreach(QString str,dirlist){
			if (str == fileName) {
				QStandardItem* f = new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon)), str);
				f->setToolTip(path + str);
				emit found(f);
			}
		}

		if (dirlist.isEmpty()) {emit searchEnded();return;}

		for (int i = 0; i<dirlist.count(); i++)dirlist[i] = path + dirlist.at(i);
		while (!dirlist.isEmpty() && isInSearch) {
			QString _tempPath = dirlist.at(0);
			QDir _tempDir(_tempPath);
			emit updateCurrentFolder(_tempPath);
			_tempDir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Dirs);
			QStringList _tempDirList = _tempDir.entryList();
			_tempDirList.removeAll(".");_tempDirList.removeAll("..");

			_tempDir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Files);
			QStringList fileslist = _tempDir.entryList();

			foreach(QString str,fileslist){
				if (str == fileName) {
					QStandardItem* f = new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon)), str);
					f->setToolTip(_tempPath);
					emit found(f);
				}
			}
			foreach(QString str,_tempDirList){
				if (str == fileName) {
					QStandardItem* f = new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon)), str);
					f->setToolTip(_tempPath + "/" + str);
					emit found(f);
				}
			}

			if(!dirlist.isEmpty()) dirlist.removeFirst();
			for (int i = 0;i<_tempDirList.count();i++) dirlist.prepend(_tempPath+"/"+_tempDirList.at(i));
		}
		isInSearch = false;
		emit searchEnded();
	}

bool SearchThread::isActive()
	{
		return isInSearch;
	}

void SearchThread::setPath(QString str)
	{
		path = str;
	}

void SearchThread::whatToSearch(QString str)
	{
		fileName = str;
	}

void SearchThread::stop()
	{
		isInSearch = false;
	}

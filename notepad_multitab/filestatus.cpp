#include "filestatus.h"

filestatus::filestatus()
	{
		reset();
	}
void filestatus::reset(){
		changed_flag = false;
		is_read_only = false;
		is_force_read_only = false;
		full_path = "";
		name = "";
		ext = "";
	}
bool filestatus::hasChanges(){
		return changed_flag;
	}
bool filestatus::isReadOnly(){
		return is_read_only;
	}

bool filestatus::isForceReadOnly()
	{
		return is_force_read_only;
	}
bool filestatus::hasPath(){
		if (full_path.length()>0)return true; else return false;
	}

void filestatus::setForceReadOnly(bool a)
	{
		is_force_read_only = a;
		is_read_only = a;
	}
void filestatus::setReadOnly(bool a){
		is_read_only = a;
	}
void filestatus::setChanged(bool a){
		changed_flag = a;
	}
QString filestatus::getExt(){

		if (full_path.size() == 0) return QString("");

		int index;
		QString s;
		index = full_path.lastIndexOf(".");
			if (index != -1){
				s = full_path.right(full_path.size()-index);
				ext = s;
				return s;
			}else{
				ext = QString("");
				return QString("");
			}
	}
QString filestatus::Path(){
		return full_path;
		extractName();
	}
void filestatus::setPath(QString s){
		full_path = s;
	}

void filestatus::setName(QString s)
	{
		name = s;
	}

QString filestatus::getName()
	{
		return name;
	}

void filestatus::extractName()
	{
		if (full_path.size() == 0) {name = QString("");return;}
		int index;
		QString s;
		index = full_path.lastIndexOf("/");
			if (index != -1){
				s = full_path.right(full_path.size()-index-1);
				name = s;
			}else{
				name = QString("");
			}
	}

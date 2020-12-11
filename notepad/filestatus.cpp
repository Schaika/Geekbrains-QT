#include "filestatus.h"

filestatus::filestatus()
	{
		changed_flag = false;
		RO_flag = false;
		full_path = "";
		ext = "";
	}
void filestatus::reset(){
		changed_flag = false;
		RO_flag = false;
		full_path = "";
		ext = "";
	}
bool filestatus::hasChanges(){
		return changed_flag;
	}
bool filestatus::isReadOnly(){
		return RO_flag;
	}
bool filestatus::hasPath(){
		if (full_path.length()>0)return true; else return false;
	}
void filestatus::setRO(bool a){
		RO_flag = a;
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
QString filestatus::getPath(){
		return full_path;
	}
void filestatus::setPath(QString s){
		full_path = s;
	}

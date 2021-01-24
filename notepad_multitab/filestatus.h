#ifndef FILESTATUS_H
#include <QString>
#define FILESTATUS_H


class filestatus
{
	bool changed_flag;
	bool is_read_only;		//флаг, что текущий файл в системе доступен только для чтения
	bool is_force_read_only;   //для режима открыть только для чтения
	QString full_path;	//полный путь к файлу
	QString ext;		//расширение текущего файла, заготовка на будущее
	QString name;
public:
	filestatus();
	void reset();
	bool hasChanges();
	bool isReadOnly();
	bool isForceReadOnly();
	bool hasPath();
	void setForceReadOnly(bool);
	void setChanged(bool);
	void setReadOnly(bool);
	QString getExt();
	QString Path();
	QString getName();
	void setPath(QString);
	void setName(QString);
	void extractName();

};

#endif // FILESTATUS_H

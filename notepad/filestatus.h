#ifndef FILESTATUS_H
#include <QString>
#define FILESTATUS_H


class filestatus
{
	bool changed_flag;
	bool is_read_only;		//флаг, что текущий файл в системе доступен только для чтения
	bool force_read_only;   //для режима открыть только для чтения
	QString full_path;	//полный путь к файлу
	QString ext;		//расширение текущего файла, заготовка на будущее
public:
	filestatus();
	void reset();
	bool hasChanges();
	bool isReadOnly();
	bool isForceReadOnly();
	bool hasPath();
	void open_readonly(bool);
	void setChanged(bool);
	void setRO(bool);
	QString getExt();
	QString getPath();
	void setPath(QString);
};

#endif // FILESTATUS_H

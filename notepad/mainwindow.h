#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filestatus.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_action_Help_triggered();
	void on_action_quit_triggered();

	void on_plainTextEdit_textChanged();

	void on_action_NewFile_triggered();

	void on_action_Open_triggered();

	void on_action_Save_triggered();

	void on_action_SaveAs_triggered();
private:
	Ui::MainWindow *ui;
	filestatus filestatus; // Класс filestatus следит за состоянием текущего файла, создается один раз
	const QString filter = tr("Текстовый файл(*.txt);;Все файлы(*.*)"); // Грамотно ли объявлять и инциализировать это в заголовочном файле?
	const QString defaultTitle = tr("Текстовый редактор");
	void openDialog();
	bool saveFile();
	bool saveAsDialog();
	void newFile();
	int askUser();
};
#endif // MAINWINDOW_H

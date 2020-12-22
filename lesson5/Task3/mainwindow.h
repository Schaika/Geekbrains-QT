#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myfilesystembrowser.h"
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
private:
	MyFileSystemBrowser *myWidget;
};
#endif // MAINWINDOW_H

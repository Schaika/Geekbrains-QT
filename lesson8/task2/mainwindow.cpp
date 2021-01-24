#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	{
		myWidget = new MyFileSystemBrowser(this,nullptr);
	}

MainWindow::~MainWindow()
	{
	}


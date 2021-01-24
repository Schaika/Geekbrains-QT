#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
	{
		QApplication a(argc, argv);
		MainWindow w;
		w.show();
		w.resize(320,480);
		return a.exec();
	}

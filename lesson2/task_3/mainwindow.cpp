#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	{
		ui->setupUi(this);

		ui->tableWidget->setColumnCount(4);
		ui->tableWidget->setRowCount(7);
		ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"ID"<<"Name"<<"IP"<<"MAC");
		for (int i =0 ; i<ui->tableWidget->rowCount(); i++ ) {
			QTableWidgetItem *ID = new QTableWidgetItem(QString::number(i+1));
			QTableWidgetItem *NAME = new QTableWidgetItem(QString(char(65+i*2)));
			QTableWidgetItem *IP = new QTableWidgetItem(QString("228.67.43.91"));
			QTableWidgetItem *MAC = new QTableWidgetItem(QString("00:50:B6:5B:CA:6A"));	//в мире моей программы все MAC адреса - одинаковые
			ui->tableWidget->setItem(i,0,ID);
			ui->tableWidget->setItem(i,1,NAME);
			ui->tableWidget->setItem(i,2,IP);
			ui->tableWidget->setItem(i,3,MAC);
		}
	}

MainWindow::~MainWindow()
	{
		delete ui;
	}

void MainWindow::on_pushButton_colorize_released()
{
		QModelIndexList indexList = ui->tableWidget->selectionModel()->selectedIndexes(); //Я не создавал модель, но tableWidget - наследник TableView и имеет доступ к методу selectionModel
		for (int i=0;i<indexList.count() ; i++) {
		QModelIndex index = indexList[i];
			int row = index.row();
			for (int j=0; j<ui->tableWidget->columnCount(); j++) {
				ui->tableWidget->item(row,j)->setBackgroundColor(QColor(255,0,0));
															/*
															*QT ругается на метод setBackgroundColor:
															*
															*warning: 'setBackgroundColor' is deprecated: Use QTableWidgetItem::setBackground() instead
															*note: 'setBackgroundColor' has been explicitly marked deprecated here
															*note: expanded from macro 'QT_DEPRECATED_X'
															*note: expanded from macro 'Q_DECL_DEPRECATED_X'
															*/
			}
		}
}

void MainWindow::on_pushButton_reset_released()
{
		for (int i =0 ; i<ui->tableWidget->rowCount(); i++ ) {
			for (int j=0; j<ui->tableWidget->columnCount(); j++ ) {
				ui->tableWidget->item(i,j)->setBackgroundColor(QColor(255,255,255));
			}
		}
}

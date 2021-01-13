#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	{
		ui->setupUi(this);
	}

MainWindow::~MainWindow()
	{
		delete ui;
	}

void MainWindow::on_pushButton_replace_clicked()
{
	ui->plainTextEdit_2->setPlainText(ui->plainTextEdit_1->toPlainText());
}

void MainWindow::on_pushButton_add_clicked()
{
	ui->plainTextEdit_2->appendPlainText(ui->plainTextEdit_1->toPlainText());
}

void MainWindow::on_pushButton_custom_clicked()
{
 ui->plainTextEdit_1->appendHtml("<font color='red'>Hello</font>");
}

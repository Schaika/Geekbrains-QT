#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtMath"
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


void MainWindow::on_pushButton_clicked()
{
		double A = ui->lineEdit_A->text().toDouble();
		double B = ui->lineEdit_B->text().toDouble();
		double angle = ui->lineEdit_angle->text().toDouble();
		if (ui->radioButton_degrees->isChecked()) angle = qDegreesToRadians(angle);
		ui->lineEdit_C->setText(
					QString::number(qSqrt(A*A+B*B-2*A*B*qCos(angle)))
					);
}

void MainWindow::on_lineEdit_A_editingFinished()
{
		ui->lineEdit_A->setText(
					QString::number(ui->lineEdit_A->text().toDouble())
					);
}

void MainWindow::on_lineEdit_B_editingFinished()
{
		ui->lineEdit_B->setText(
					QString::number(ui->lineEdit_B->text().toDouble())
					);
}

void MainWindow::on_lineEdit_angle_editingFinished()
{
		ui->lineEdit_angle->setText(
					QString::number(ui->lineEdit_angle->text().toDouble())
					);
}

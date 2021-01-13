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

int Discriminant(double A, double B, double C){
	return B*B-4*A*C;
	}

QString returnEquation(double A, double B, double C){
	QString out;
	//A
	if (A>0){
		if (A!=1) out.append(QString::number(A));
		out.append("x^2");
	}else if (A<0){
		if (A!=-1) out.append(QString::number(A)); else out.append("-");
		out.append("x^2");
	}
	//B
	if (B<0){
		if (B!=-1) out.append(QString::number(B)); else out.append("-");
		out.append("x");
	}else if(B>0){
		if (A!=0){
			out.append("+");
			if (B!=1) out.append(QString::number(B));
			out.append("x");
		}else{
			if (B!=1) out.append(QString::number(B));
			out.append("x");
		}
	}
	//C
	if (C<0){
		out.append(QString::number(C));
	}else if(C>0){
		if (A!=0 || B!=0){
			out.append("+");
			out.append(QString::number(C));
		}else{
			out.append(QString::number(C));
		}
	}
	if(A || B){
		out.append("=0");
	}
	return out;
	};

void MainWindow::on_buttonSolve_clicked()
{
		double A = ui->lineA->text().toDouble();
		double B = ui->lineB->text().toDouble();
		double C = ui->lineC->text().toDouble();
		ui->lineRoot1->setText("");
		ui->lineRoot2->setText("");
		//no input
		if (A==0 && B==0 && C==0){
			ui->label_typeOf->setText("Please input a valid equation!");
			return;
		}
		//line equation with no roots
		if (A==0 && B==0 && C!=0){
			ui->label_typeOf->setText("Line equation with no roots");
			return;
		}
		//line equation with roots
		if (A==0 && B!=0){
			ui->lineRoot1->setText(QString::number(-C/B));
			ui->lineRoot2->setText("");
			ui->label_typeOf->setText("Line equation with 1 root");
			return;
		}
		//quadratic equation
		if (A!=0){
			int D = Discriminant(A,B,C);
			QString root1;
			QString root2;
			if (D<0){
				D=abs(D);
				//root 1
				root1.append(QString::number(-B/2*A));
				root1.append("+");
				root1.append(QString::number(qSqrt(D)/2*A));
				root1.append("i");
				//root 2
				root2.append(QString::number(-B/2*A));
				root2.append("-");
				root2.append(QString::number(qSqrt(D)/2*A));
				root2.append("i");
				ui->lineRoot1->setText(root1);
				ui->lineRoot2->setText(root2);
				ui->label_typeOf->setText("Quadratic equation with imaginary roots");
				return;
			}else if (D==0){
				root1.append(QString::number(-B/2*A));
				ui->lineRoot1->setText(root1);
				ui->lineRoot2->setText(root2);
				ui->label_typeOf->setText("Quadratic equation with one root");
				return;
			}else if (D>0){
				D=abs(D);
				//root 1
				root1.append(QString::number((-B+qSqrt(D))/2*A));
				//root 2
				root2.append(QString::number((-B-qSqrt(D))/2*A));
				ui->lineRoot1->setText(root1);
				ui->lineRoot2->setText(root2);
				ui->label_typeOf->setText("Quadratic equation with two roots");
			}

		}

}

void MainWindow::on_lineA_editingFinished()
{
	ui->lineA->setText(
				QString::number(ui->lineA->text().toDouble())
				);
	ui->lineEquation->setText(returnEquation(ui->lineA->text().toDouble(),ui->lineB->text().toDouble(),ui->lineC->text().toDouble()));
}

void MainWindow::on_lineB_editingFinished()
{
	ui->lineB->setText(
				QString::number(ui->lineB->text().toDouble())
				);
	ui->lineEquation->setText(returnEquation(ui->lineA->text().toDouble(),ui->lineB->text().toDouble(),ui->lineC->text().toDouble()));
}

void MainWindow::on_lineC_editingFinished()
{
		ui->lineC->setText(
					QString::number(ui->lineC->text().toDouble())
					);
		ui->lineEquation->setText(returnEquation(ui->lineA->text().toDouble(),ui->lineB->text().toDouble(),ui->lineC->text().toDouble()));
}

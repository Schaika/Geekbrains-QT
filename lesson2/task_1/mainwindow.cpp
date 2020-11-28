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


void MainWindow::on_plainTextEdit_textChanged()
{
	SpecialSymbol parseSymbols;
	if (parseSymbols.changes(ui->plainTextEdit->toPlainText())){
		ui->plainTextEdit->setPlainText(parseSymbols.getText());
	};
}

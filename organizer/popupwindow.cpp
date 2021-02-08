#include "popupwindow.h"
#include "ui_popupwindow.h"

popupWindow::popupWindow(QWidget *parent, QSqlQueryModel* model) :
	QDialog(parent),
	ui(new Ui::popupWindow)
	{
		ui->setupUi(this);
		model->setParent(this);
		ui->tableView->setModel(model);
	}

popupWindow::~popupWindow()
	{
		delete ui;
	}

void popupWindow::updateModel(QSqlQueryModel* newModel)
	{
		ui->tableView->setModel(newModel);
		ui->tableView->show();
	}

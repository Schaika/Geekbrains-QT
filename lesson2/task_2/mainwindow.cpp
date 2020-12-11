#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QFile>
//я создал 2 функции, чтобы не копировать один и тот же код на кнопки
// initModel собирает модель из глобального листа строк
// updateModel создает указатель на новую модель, инициализует ее и удаляет старую модель
// я лишь когда сделал задание, смог найти способ как сделать его <italic> более правильно </italic>
// наверное по заданию нужно было делать с помощью removeRow() и insertRow() из класса QAbstractItemModel и работать с одной моделью
// но такая реализация тоже работает
// если это совсем неправильно, я переделаю
QStringList list {"C++", "Python", "Java", "C#", "PHP", "JavaScript"};
void initModel(QAbstractItemModel *model){
		for (int i=0; i<model->rowCount(); i++) {
			QModelIndex index = model->index(i,0);
			QString str = list[i];
			model->setData(index,str,Qt::DisplayRole);
			QString fileName = QCoreApplication::applicationDirPath()+"/ico/"+str+".png"; //собираем имя файла с абсолютным путем
			if (QFile::exists(fileName)){
					model->setData(index,QIcon(fileName),Qt::DecorationRole);
				}else{
					model->setData(index,QApplication::style()->standardIcon(QStyle::SP_FileIcon),Qt::DecorationRole);
			}
		}
	}

QStandardItemModel*  updateModel(QAbstractItemModel *model){
		QStandardItemModel *newModel = new QStandardItemModel(list.size(),1,model->parent());
		initModel(newModel);
		delete model;
		return newModel;
	};

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	{
		QStandardItemModel *model = new QStandardItemModel(list.size(),1,this);
		ui->setupUi(this);
		initModel(model);
		ui->listView->setModel(model);
	}

MainWindow::~MainWindow()
	{
		delete ui;
	}


void MainWindow::on_checkBox_IconMode_released()
{
		if (ui->checkBox_IconMode->isChecked()){
			ui->listView->setViewMode(QListView::IconMode);
		}else{
			ui->listView->setViewMode(QListView::ListMode);
		}
}

void MainWindow::on_pushButton_REMOVE_released()
{
	int curIndex = ui->listView->currentIndex().row();
	if (curIndex != -1){
	list.removeAt(curIndex);
	ui->listView->setModel(updateModel(ui->listView->model()));
	}
}

void MainWindow::on_pushButton_ADD_released()
{
		int curIndex = ui->listView->currentIndex().row();
		if (ui->lineEdit->text() != ""){
				if (curIndex != -1)
					list.insert(curIndex+1,ui->lineEdit->text());
				else
					list.append(ui->lineEdit->text());
		ui->listView->setModel(updateModel(ui->listView->model()));
		}
}

void MainWindow::on_pushButton_RENAME_released()
{
		int curIndex = ui->listView->currentIndex().row();
		if (ui->lineEdit->text() != "" && curIndex != -1){
		list[curIndex]=ui->lineEdit->text();
		ui->listView->setModel(updateModel(ui->listView->model()));
		}
}

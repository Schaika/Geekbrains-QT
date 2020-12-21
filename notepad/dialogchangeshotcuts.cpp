#include "dialogchangeshotcuts.h"
#include "ui_dialogchangeshotcuts.h"

// маленькое диалоговое окно в котором можно изменить клавиатурные сокращения
// главное окно передает QStringList конструктору (возможно следовало использовать QMap)
dialogChangeShotcuts::dialogChangeShotcuts(QWidget *parent,QStringList list) :
	QDialog(parent),
	ui(new Ui::dialogChangeShotcuts)
	{
		ui->setupUi(this);
		ui->keySequenceEdit_new->setKeySequence(list.at(0));
		ui->keySequenceEdit_open->setKeySequence(list.at(1));
		ui->keySequenceEdit_openRO->setKeySequence(list.at(2));
		ui->keySequenceEdit_save->setKeySequence(list.at(3));
		ui->keySequenceEdit_saveAs->setKeySequence(list.at(4));
		ui->keySequenceEdit_help->setKeySequence(list.at(5));
		ui->keySequenceEdit_exit->setKeySequence(list.at(6));
	}

dialogChangeShotcuts::~dialogChangeShotcuts()
	{
		delete ui;
	}


void dialogChangeShotcuts::on_pushButton_discard_released()
{
	// если нажата отмена ничего не делаем и закрываем окно
	this->close();
}

void dialogChangeShotcuts::on_pushButton_accept_released()
{
	QStringList newList;
	newList.append(ui->keySequenceEdit_new->keySequence().toString());
	newList.append(ui->keySequenceEdit_open->keySequence().toString());
	newList.append(ui->keySequenceEdit_openRO->keySequence().toString());
	newList.append(ui->keySequenceEdit_save->keySequence().toString());
	newList.append(ui->keySequenceEdit_saveAs->keySequence().toString());
	newList.append(ui->keySequenceEdit_help->keySequence().toString());
	newList.append(ui->keySequenceEdit_exit->keySequence().toString());
	emit sendList(newList);
	this->close();
}

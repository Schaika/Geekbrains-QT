#include "dialogshortcuts.h"
#include "ui_dialogshortcuts.h"

DialogShortcuts::DialogShortcuts(QList<QAction*> p_list,QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogShortcuts)
	{
		ui->setupUi(this);
		this->setWindowTitle(tr("Shortcut keys"));
		list = p_list;
		gridLayout = new QGridLayout(this);
		this->setLayout(gridLayout);

		int ID = 0;

		for (int i = 0; i<list.length(); i++) {
			QAction* obj = list.at(i);
			QLabel* label = new QLabel(obj->text(),this);
			gridLayout->addWidget(label,ID,0,1,3);
			QKeySequenceEdit* textField = new QKeySequenceEdit(obj->shortcut(),this);
			connect(textField,SIGNAL(keySequenceChanged(QKeySequence)),this,SLOT(Change()));
			keylist.insert(i,textField);
			textField->setObjectName(obj->objectName());
			gridLayout->addWidget(textField,ID,3,1,1);
			ID++;
		}

		ok = new QPushButton(tr("Save"),this);
		gridLayout->addWidget(ok,ID+1,0,1,3);
		connect(ok,SIGNAL(pressed()),this,SLOT(Ok()));
		cancel = new QPushButton(tr("Cancel"),this);
		gridLayout->addWidget(cancel,ID+1,3,1,1);
		connect(cancel,SIGNAL(pressed()),this,SLOT(Cancel()));
	}

DialogShortcuts::~DialogShortcuts()
	{
		delete ui;
	}

void DialogShortcuts::Ok()
	{
		for (int i = 0; i<list.length(); i++) {
			QAction* obj = list.at(i);
			QKeySequenceEdit* keySeq = keylist.at(i);
			if(obj->objectName() == keySeq->objectName())
				obj->setShortcut(keySeq->keySequence());
		}
		safeToClose = true;
		this->close();
	}

void DialogShortcuts::Cancel()
	{
		this->close();
	}

void DialogShortcuts::Change()
	{
		changed = true;
	}

void DialogShortcuts::closeEvent(QCloseEvent* event)
	{

		if (safeToClose){
			 event->accept();
			 return;
		}
		if (!changed){
			event->accept();
			return;
		}
		QMessageBox msgBox;
			msgBox.setWindowTitle(tr("Do you want to save your changes?"));
			msgBox.setText(tr("Do you want to save your changes?"));
			msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel);
			msgBox.setButtonText(QMessageBox::Save, tr("Save"));
			msgBox.setButtonText(QMessageBox::No, tr("No"));
			msgBox.setButtonText(QMessageBox::Cancel, tr("Cancel"));
			msgBox.setDefaultButton(QMessageBox::Save);
			msgBox.setIcon(QMessageBox::Question);
			switch (msgBox.exec()) {
			case QMessageBox::Save:
					Ok();
				break;
			case QMessageBox::No:
					event->accept();
				break;
			case QMessageBox::Cancel:
					event->ignore();
				break;
			default:
				break;
			}
	}

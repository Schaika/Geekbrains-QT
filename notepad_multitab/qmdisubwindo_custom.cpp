#include "qmdisubwindo_custom.h"



QMdiSubWindo_custom::QMdiSubWindo_custom(QWidget* parent, Qt::WindowFlags flags):QMdiSubWindow(parent,flags)
	{

	}

void QMdiSubWindo_custom::closeEvent(QCloseEvent* closeEvent)
	{
		QTextEdit_custom *obj =  (QTextEdit_custom*)widget();
		if (obj->filestatus.hasChanges()){
		QMessageBox msgBox;
			msgBox.setWindowTitle(tr("The document has been modified."));
			msgBox.setText(tr("The document has been modified."));
			msgBox.setInformativeText(tr("Do you want to save your changes?"));
			msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel);
			msgBox.setButtonText(QMessageBox::Save, tr("Save"));
			msgBox.setButtonText(QMessageBox::No, tr("No"));
			msgBox.setButtonText(QMessageBox::Cancel, tr("Cancel"));
			msgBox.setDefaultButton(QMessageBox::Save);
			msgBox.setIcon(QMessageBox::Question);
			switch (msgBox.exec()) {
			case QMessageBox::Save:
				emit closeTab(this);
					if (obj->filestatus.hasChanges()) closeEvent->ignore(); else closeEvent->accept();
					return;
				break;
			case QMessageBox::No:
				closeEvent->accept();
					return;
				break;
			case QMessageBox::Cancel:
				closeEvent->ignore();
					return;
				break;
			default:
				break;
			}
		}else{closeEvent->accept();}
	}

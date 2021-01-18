#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	{
		ui->setupUi(this);
		on_actionRussian_triggered();
		this->setWindowIcon(QIcon(":/src/ico/res/text-editor-logo.svg"));
		mdiArea = ui->mdiArea;
		mdiArea->setViewMode(QMdiArea::TabbedView);
		mdiArea->setTabsClosable(true);
		mdiArea->setTabsMovable(true);
		//ишем указатель на объект QTabBar внутри QMdiArea

			QList<QTabBar*> list = mdiArea->findChildren<QTabBar*>();
			m_pMdiAreaTabBar = list[0];
			if (m_pMdiAreaTabBar != 0) {
				m_pMdiAreaTabBar->setExpanding(false);
				m_pMdiAreaTabBar->setContextMenuPolicy(Qt::NoContextMenu); // добавить меню познее
			}
			on_mdiArea_subWindowActivated(nullptr);
	}

MainWindow::~MainWindow()
	{
		delete ui;
	}

void MainWindow::add_window(QString window_name,QTextEdit_custom *obj)
	{
		QMdiSubWindo_custom* sw = new QMdiSubWindo_custom( mdiArea );
		if (obj==nullptr) obj = new QTextEdit_custom();
		obj->setParent(sw);
		connect(obj,SIGNAL(textChanged()),this,SLOT(textchanged()));
		connect(sw,SIGNAL(closeTab(QMdiSubWindo_custom*)),this,SLOT(closeTabEvent(QMdiSubWindo_custom*)));
		sw->setWidget(obj);
		sw->setAttribute( Qt::WA_DeleteOnClose );
		if (window_name.isEmpty())
			{
				sw->setWindowTitle(tr("New file.txt"));
			}
		else
			{
				sw->setWindowTitle(window_name);
			}
		obj->filestatus.setName(sw->windowTitle());
		mdiArea->addSubWindow( sw );
		sw->showMaximized();
		on_mdiArea_subWindowActivated(sw);
	}

void MainWindow::add_window()
	{
		auto obj = new QTextEdit_custom();
		add_window(QString(),obj);
	}

void MainWindow::setMainWindowTitle(QString text)
	{
		if (text.isEmpty())	this->setWindowTitle(projectName); else this->setWindowTitle(text + " - " + projectName);
	}

bool MainWindow::openDialog(QTextEdit_custom *obj, QString path){
		QString filename = QFileDialog::getOpenFileName(this, tr("Open file..."), path.isEmpty() ? QDir::current().path() : path, tr("Text Documents (*.txt);;All files(*.*)")); //если путь к файлу есть - открывает диалоговое окно в папке с текущим файлом, если нет - открывает окно в папке с программой
			if (filename.length()>0){
				obj->filestatus.setPath(filename);
				obj->filestatus.extractName();
				obj->filestatus.getExt();
				QFile file(filename);
				QFileInfo info(file);
						obj->filestatus.setReadOnly(!info.isWritable()||obj->filestatus.isForceReadOnly());
					if(file.open(QIODevice::ExistingOnly | QIODevice::ReadOnly)){
						QByteArray bytedata = file.readAll();
						obj->setPlainText(bytedata.data());
						return true;
					}
			}
			return false;
	}

void MainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow *window)
	{
		QString partTitle = "";
					if (window == nullptr) {setMainWindowTitle(partTitle);return;}

		auto obj = (QTextEdit_custom*)window->widget();

		//иконка
		if (obj->filestatus.isReadOnly())
		{window->setWindowIcon(QIcon(":/src/ico/res/subWindow-readOnly.png"));if(obj->filestatus.isForceReadOnly())partTitle = tr("(forced read-only) ");} // readOnly
		else if (obj->filestatus.hasChanges())
		{window->setWindowIcon(QIcon(":/src/ico/res/subWindow_notSaved.png"));partTitle = "* ";} // NOT saved
		else
		window->setWindowIcon(QIcon(":/src/ico/res/subWindow_Saved.png")); // saved

		//заголок окна
		if (obj->filestatus.hasPath()){
			partTitle += obj->filestatus.Path();
		}else{
			partTitle += window->windowTitle();
		}
		setMainWindowTitle(partTitle);

		//костыль для принудительного режима только для чтения
		obj->setReadOnly(obj->filestatus.isForceReadOnly());
		//заголок вкладки
		window->setWindowTitle(obj->filestatus.getName());
		//кнопка сохранить
		//ui->actionSave->QAction::setEnabled(!(!obj->filestatus.hasPath() || obj->filestatus.isReadOnly() || obj->filestatus.isForceReadOnly()));
	}

void MainWindow::on_actionAbout_triggered()
	{
		auto obj = new QTextEdit_custom();
		obj->filestatus.setForceReadOnly(true);
		obj->filestatus.setPath(":/src/txt/res/readme_"+language+".txt");
		QFile file(obj->filestatus.Path());
			if(file.open(QIODevice::ReadOnly)){
				QByteArray ba = file.readAll();
				obj->setPlainText(ba.data());
			}
		obj->filestatus.setPath("");
		add_window(tr("About program"),obj);
	}

void MainWindow::on_actionNew_file_triggered()
	{
		add_window();
	}

void MainWindow::on_actionOpen_triggered()
	{
		QString path = "";
		auto _obj = getCurrentQTextEdit();
		if (_obj != nullptr) path = _obj->filestatus.Path();
		QTextEdit_custom *obj = new QTextEdit_custom();
		if (openDialog(obj,path)) add_window(obj->filestatus.getName(),obj); else delete obj;
	}

void MainWindow::textchanged()
	{
		auto obj = (QTextEdit_custom*)sender();
		obj->filestatus.setChanged(true);
		on_mdiArea_subWindowActivated((QMdiSubWindow*)obj->parent());
	}

void MainWindow::on_actionLight_triggered()
{
		qApp->setStyleSheet("");
}

void MainWindow::on_actionDark_triggered()
{
		qApp->setStyleSheet("QMenuBar {background-color: #232323; color:white}"
							"QMenuBar::item:selected {background: #27609A}"
							"QMenu {background-color: #232323; color:white}"
							"QMenu::item:selected {background: #27609A}"
							"QMainWindow {background-color: #232323}"
							"QTabBar::tab     {background: #292929}"
							"QTabBar::tab::selected     {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #323232, stop: 1 #2c2c2c)}"
							"QTabBar::tab::hover     {background: #353535}"
							"QDialog {background-color: #333333}"
							"QLabel {color:white}"
							"QTextEdit {background-color: #000000; color:white}"
							"QLineEdit {background-color: #000000; color:white}"
							"QPushButton {border: 1px solid #27609A; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #323232, stop: 1 #2c2c2c); color:white;min-height: 21px;padding-left: 25px;padding-right: 25px}"
							"QPushButton:hover {border: 2px solid #27609A; background-color: #353535; padding-left: 24px; padding-right: 24px}");
	}

bool MainWindow::saveAsDialog(QMdiSubWindo_custom* sw){
		if (sw == nullptr) return false;
		auto obj = (QTextEdit_custom*)sw->widget();
		QString filename = QFileDialog::getSaveFileName(this, tr("Save file as..."), obj->filestatus.hasPath() ? obj->filestatus.Path() : QString(QDir::current().path() + "/" + obj->filestatus.getName()), tr("Text Documents (*.txt);;All files(*.*)"));
		if (filename.length()>0){
			obj->filestatus.setPath(filename);
			obj->filestatus.extractName();
			obj->filestatus.getExt();
			return true;
		}else return false;
	}

QMdiSubWindo_custom* MainWindow::getCurrentQMdiSubWindow()
	{
		auto sw = (QMdiSubWindo_custom*)mdiArea->activeSubWindow();
			if (sw == nullptr) return nullptr;
			return sw;
	}

QTextEdit_custom* MainWindow::getCurrentQTextEdit()
	{
		auto sw = getCurrentQMdiSubWindow();
		if (sw == nullptr) return nullptr;
		QTextEdit_custom* obj = (QTextEdit_custom*)sw->widget();
		return obj;
	}

bool MainWindow::saveFile(QMdiSubWindo_custom* sw){
		if (sw == nullptr) return false;
		auto obj = (QTextEdit_custom*)sw->widget();
		if(obj->filestatus.Path().isEmpty() || obj->filestatus.isReadOnly() == true) if(!saveAsDialog(sw)) return false;
		QFile file(obj->filestatus.Path());
			if(file.open(QIODevice::WriteOnly)){
				QString data = obj->toPlainText();
				QByteArray bytedata = data.toUtf8();
				file.write(bytedata,bytedata.size());
				obj->filestatus.setChanged(false);
				return true;
			}else return false;
	}

void MainWindow::closeTabEvent(QMdiSubWindo_custom* sw)
	{
		saveFile(sw);
	}

void MainWindow::on_actionSave_triggered()
{
		auto sw = getCurrentQMdiSubWindow();
		if (sw!=nullptr) saveFile(sw);
		on_mdiArea_subWindowActivated(sw);
}

void MainWindow::on_actionCopy_Text_Format_triggered()
{
		auto obj = getCurrentQTextEdit();
		if (obj == nullptr) return;
		formatBuffer = obj->textCursor().charFormat();
}

void MainWindow::on_actionApply_Text_Format_triggered()
{
		auto obj = getCurrentQTextEdit();
		if (obj == nullptr) return;
		if (obj->filestatus.isReadOnly()) return;
		obj->textCursor().setCharFormat(formatBuffer);
}

void MainWindow::on_actionCenter_triggered()
{
		auto obj = getCurrentQTextEdit();
		if (obj == nullptr) return;
		if (obj->filestatus.isReadOnly()) return;
		QTextCursor cursor = obj->textCursor();
		QTextBlockFormat textBlockFormat = cursor.blockFormat();
		textBlockFormat.setAlignment(Qt::AlignCenter);
		cursor.mergeBlockFormat(textBlockFormat);
		obj->setTextCursor(cursor);
}

void MainWindow::on_actionLeft_triggered()
{
		auto obj = getCurrentQTextEdit();
		if (obj == nullptr) return;
		if (obj->filestatus.isReadOnly()) return;
		QTextCursor cursor = obj->textCursor();
		QTextBlockFormat textBlockFormat = cursor.blockFormat();
		textBlockFormat.setAlignment(Qt::AlignLeft);
		cursor.mergeBlockFormat(textBlockFormat);
		obj->setTextCursor(cursor);
}

void MainWindow::on_actionRight_triggered()
{
		auto obj = getCurrentQTextEdit();
		if (obj == nullptr) return;
		if (obj->filestatus.isReadOnly()) return;
		QTextCursor cursor = obj->textCursor();
		QTextBlockFormat textBlockFormat = cursor.blockFormat();
		textBlockFormat.setAlignment(Qt::AlignRight);
		cursor.mergeBlockFormat(textBlockFormat);
		obj->setTextCursor(cursor);
}

void MainWindow::on_actionOpen_force_read_only_triggered()
{
		QString path = "";
		auto _obj = getCurrentQTextEdit();
		if (_obj != nullptr) path = _obj->filestatus.Path();
		QTextEdit_custom *obj = new QTextEdit_custom();
		obj->filestatus.setForceReadOnly(true);
		if (openDialog(obj,path)) add_window(obj->filestatus.getName(),obj); else delete obj;
}

void MainWindow::on_actionSave_as_triggered()
{
	auto sw = getCurrentQMdiSubWindow();
	if(saveAsDialog(sw))saveFile(sw);
}

void MainWindow::on_actionClose_triggered()
{
		auto sw = getCurrentQMdiSubWindow();
		sw->close();
}

void MainWindow::on_actionSave_all_triggered()
{
	QList<QMdiSubWindo_custom*> list = mdiArea->findChildren<QMdiSubWindo_custom*>();
	foreach(QMdiSubWindo_custom* sw,list){
		QTextEdit_custom* obj = (QTextEdit_custom*)sw->widget();
		if(obj->filestatus.hasChanges()) {
			if(!saveFile(sw)){return;};
			on_mdiArea_subWindowActivated(sw);
		}
	}
}

void MainWindow::on_actionClose_all_triggered()
{
		QList<QMdiSubWindo_custom*> list = mdiArea->findChildren<QMdiSubWindo_custom*>();
		foreach(QMdiSubWindo_custom* sw,list){
			QTextEdit_custom* obj = (QTextEdit_custom*)sw->widget();
			if(obj->filestatus.hasChanges()) {
				if(!saveFile(sw)){return;};
			}
		}
		foreach(QMdiSubWindo_custom* sw,list){
			sw->close();
		}
}

void MainWindow::on_actionFont_triggered()
{
		auto obj = getCurrentQTextEdit();
		if (obj == nullptr) return;
		QFont font = obj->textCursor().charFormat().font(); // получаем текущий шрифт
		QFontDialog fntDlg(font,this);

		bool ok;
		font = fntDlg.getFont(&ok);
		if (ok){
			QTextCharFormat fmt;
			fmt.setFont(font);
			obj->textCursor().setCharFormat(fmt);
		}
}

void MainWindow::on_actionExit_triggered()
{
	qApp->closeAllWindows();
}
void MainWindow::closeEvent(QCloseEvent* event){

		QList<QMdiSubWindo_custom*> list_sw = mdiArea->findChildren<QMdiSubWindo_custom*>();
		QList<QMdiSubWindo_custom*> list_obj;
		foreach(QMdiSubWindo_custom* sw,list_sw){
			QTextEdit_custom* obj = (QTextEdit_custom*)sw->widget();
			if(obj->filestatus.hasChanges()) {list_obj.append(sw);}
		}
		int files = list_obj.count();
		if (files)
		{

			QMessageBox msgBox;
				msgBox.setWindowTitle(tr("Do you want to save your changes?"));
				msgBox.setText(tr("There are %1 documents with unsaved changes").arg(files));
				msgBox.setInformativeText(tr("Do you want to save them now?"));
				msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel);
				msgBox.setButtonText(QMessageBox::Save, tr("Save"));
				msgBox.setButtonText(QMessageBox::No, tr("No"));
				msgBox.setButtonText(QMessageBox::Cancel, tr("Cancel"));
				msgBox.setDefaultButton(QMessageBox::Save);
				msgBox.setIcon(QMessageBox::Question);
				switch (msgBox.exec())
					{
						case QMessageBox::Save:
					foreach(QMdiSubWindo_custom* _sw,list_obj)
						{
							bool result = saveFile(_sw);on_mdiArea_subWindowActivated(_sw);
							if(!result) {event->ignore();return;}
						}
					event->accept();
							break;
						case QMessageBox::No:
								event->accept();
							return;
							break;
						case QMessageBox::Cancel:
								event->ignore();
							return;
							break;
						default:
							break;
					}
			}else{event->accept();}
	}
void MainWindow::keyPressEvent(QKeyEvent *event){
		auto obj = getCurrentQTextEdit();
		if (obj == nullptr) return;
		if(event->key() == Qt::Key_F5){
			QTextCursor cursor = obj->textCursor();
			QDateTime now = QDateTime::currentDateTime();
			cursor.insertText(QString(now.time().toString()) + " " + now.date().toString());
			obj->setTextCursor(cursor);
		}
	}

void MainWindow::paintEvent(QPaintEvent* event)
	{
		Q_UNUSED(event)
		if(!first)
		{
			first = true;
			add_window();
		}
	}

void MainWindow::on_actionPrint_triggered()
{
		auto obj = getCurrentQTextEdit();
		if (obj == nullptr) return;
		QPrinter printer;
		QPrintDialog dlg(&printer, this);
		dlg.setWindowTitle(tr("Print..."));
		if (dlg.exec() == QDialog::Accepted){
			obj->print(&printer);
		}
}

void MainWindow::on_actionEnglish_triggered()
{
		qApp->removeTranslator(&translator);
		language = "en_US";
		ui->retranslateUi(this); // без этой команды не обновляет интерфейс
		on_mdiArea_subWindowActivated(nullptr);
}

void MainWindow::on_actionRussian_triggered()
{
		translator.load(":/new/lang/notepad_multitab_ru_RU.qm");
		qApp->installTranslator(&translator);
		language = "ru_RU";
		ui->retranslateUi(this);
		on_mdiArea_subWindowActivated(nullptr);
}

void MainWindow::on_actionKey_Shortcuts_triggered()
{
		QList<QAction*> list = this->findChildren<QAction*>(QString(),Qt::FindDirectChildrenOnly);
		QList<QString> blacklist = {"actionEnglish","actionRussian","actionLight","actionDark","actionKey_Shortcuts"};
		QList<QAction*> marked;
		foreach(QAction* obj,list){
			foreach(QString name,blacklist){
				if (obj->objectName() == name) marked.append(obj);
			}
		}

		foreach(QAction* obj,marked) list.removeAll(obj);

	DialogShortcuts window(list,this);
	window.setModal(true);
	window.setWindowFlags(window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
	window.exec();
}

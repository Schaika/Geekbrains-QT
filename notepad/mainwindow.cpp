#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogchangeshotcuts.h"
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	{
		ui->setupUi(this);
		this->setWindowTitle(QString(tr("Новый файл - ")) + defaultTitle);
		this->setWindowIcon(QIcon(":/src/ico/res/text-editor-logo.svg"));
		initShortcutList();
	}
MainWindow::~MainWindow()
	{
		delete ui;
	}
int MainWindow::askUser(){
		QMessageBox msgBox;
			msgBox.setWindowTitle(tr("Файл был изменен."));
			msgBox.setText(tr("Файл был изменен."));
			msgBox.setInformativeText(tr("Вы хотите сохранить изменения?"));
			msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel);
			msgBox.setButtonText(QMessageBox::Save, tr("Сохранить"));
			msgBox.setButtonText(QMessageBox::No, tr("Нет"));
			msgBox.setButtonText(QMessageBox::Cancel, tr("Отмена"));
			msgBox.setDefaultButton(QMessageBox::Save);
			msgBox.setIcon(QMessageBox::Question);
			return msgBox.exec();
	}

void MainWindow::actualizeForm()
	{
		ui->action_Save->QAction::setEnabled(!(!filestatus.hasPath() || filestatus.isReadOnly() || filestatus.isForceReadOnly())); // убирает кнопку сохранения, если файл только для чтения или нет пути к файлу в filestatus.full_path
		ui->plainTextEdit->setReadOnly(filestatus.isForceReadOnly()); // блокирует изменения в главном поле ввода, если файл принудительно открыт только для чтения
	}
void MainWindow::openDialog(){
		QString filename = QFileDialog::getOpenFileName(this, tr("Открыть файл..."), filestatus.hasPath() ? filestatus.getPath() : QDir::current().path(), tr("Текстовый файл(*.txt);;Все файлы(*.*)")); //если путь к файлу есть - открывает диалоговое окно в папке с текущим файлом, если нет - открывает окно в папке с программой
			if (filename.length()>0){
				filestatus.setPath(filename);
				filestatus.getExt(); //Получаем расширение файла. Расширение нигде не используется, заготовка на будущее
				QFile file(filename);
				QFileInfo info(file);
							filestatus.setRO(!info.isWritable());
							if (filestatus.isForceReadOnly()){
									this->setWindowTitle("(" + filename + ")" + QString(tr("  -- открыто только для чтения -- ")) + defaultTitle);
							}else{
								if (filestatus.isReadOnly()){
									this->setWindowTitle("(" + filename + ")" + QString(tr("  -- файл только для чтения -- ")) + defaultTitle); //если файл только для чтения - в заголовке программмы рядом с путем будет соответсвубщая надпись
								}else{
									this->setWindowTitle("(" + filename + ") - " + defaultTitle);
								}
							}

					if(file.open(QIODevice::ExistingOnly | QIODevice::ReadOnly)){
						QByteArray bytedata = file.readAll();
						ui->plainTextEdit->setPlainText(bytedata.data());
						filestatus.setChanged(false);
					}
			}
		actualizeForm();
	}
// saveAsDialog() - всего лишь выводит окно с выбором пути для сохранения файла, но ничего не сохраняет
bool MainWindow::saveAsDialog(){
		QString filename = QFileDialog::getSaveFileName(this, tr("Сохранить файл как..."), filestatus.hasPath() ? filestatus.getPath() : QDir::current().path() + QString(tr("/Новый файл")), tr("Текстовый файл(*.txt);;Все файлы(*.*)"));
		if (filename.length()>0){
			filestatus.reset();
			filestatus.setPath(filename);
			QString ext = filestatus.getExt();
			this->setWindowTitle("(" + filename + ") - " + defaultTitle);
			return true;
		}else return false;
	}
// saveFile() проверяет можно ли писать в файл и есть ли путь к нему (в случае если файл новый)
bool MainWindow::saveFile(){
		if(filestatus.getPath().length()==0|| filestatus.isReadOnly() == true) if(!saveAsDialog()) return false;
		QFile file(filestatus.getPath());
			if(file.open(QIODevice::WriteOnly)){
				QString data = ui->plainTextEdit->toPlainText();
				QByteArray bytedata = data.toUtf8();
				file.write(bytedata,bytedata.size());
				return true;
			}else return false;
	}
void MainWindow::on_plainTextEdit_textChanged()
{
	filestatus.setChanged(true);
}
void MainWindow::newFile(){
		filestatus.reset();
		this->setWindowTitle(QString(tr("Новый файл - ")) + defaultTitle);
		ui->plainTextEdit->clear();
		filestatus.setChanged(false);
		actualizeForm();
	}
void MainWindow::on_action_NewFile_triggered()
{
	if(filestatus.hasChanges()){ //проверка перед созданием нового файла, если текущий файл имеет изменения, то предлагаем сохранить их

		switch (askUser()) {
		case QMessageBox::Save:
				if(saveFile()) newFile(); //если удалось сохранить файл, то можно создавать новый
			break;
		case QMessageBox::No:
			newFile();
			break;
		case QMessageBox::Cancel:
				return;
			break;
		default:
			break;
		}
	}else{
		newFile();
	}
}

void MainWindow::openFileCheck(){
		if(filestatus.hasChanges()){ //такая же проверка, что и при создани файла
			switch (askUser()) {
			case QMessageBox::Save:
					if(saveFile()) openDialog();
				break;
			case QMessageBox::No:
				openDialog();
				break;
			case QMessageBox::Cancel:
					return;
				break;
			default:
				break;
			}
		}else{
			openDialog();
		}
	}

void MainWindow::on_action_Open_triggered()
{
	filestatus.open_readonly(false);
	openFileCheck();
}


void MainWindow::on_action_OpenRO_triggered()
{
	filestatus.open_readonly(true);
	openFileCheck();
}

void MainWindow::on_action_Save_triggered()
{
	if(saveFile()) filestatus.setChanged(false);
}

void MainWindow::on_action_SaveAs_triggered()
{
	if(saveAsDialog()) if(saveFile()) filestatus.setChanged(false);
}

void MainWindow::on_action_quit_triggered()
{
	  qApp->exit(0); // пока не нашел функцию, которая позволяет перехватить (и даже отменить) закрытие программы, если нажат крестик или Alt+F4. Потому не стал добавлять проверку и предлагать сохранить файл на этой кнопке, иначе было бы странно.
}
void MainWindow::on_action_Help_triggered()
{

		if(filestatus.hasChanges()){
				QMessageBox msgBox;
					msgBox.setWindowTitle(tr("Файл был изменен."));
					msgBox.setText(tr("Файл был изменен."));
					msgBox.setInformativeText(tr("Вы хотите сохранить текущие изменения перед загрузкой справки?"));
					msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
					msgBox.setButtonText(QMessageBox::Yes, tr("Да"));
					msgBox.setButtonText(QMessageBox::No, tr("Нет"));
					msgBox.setButtonText(QMessageBox::Cancel, tr("Отмена"));
					msgBox.setDefaultButton(QMessageBox::Save);
					msgBox.setIcon(QMessageBox::Question);
				int ret = msgBox.exec();
				switch (ret) {
					case QMessageBox::Yes:
							if(!saveFile()) return; //если файл не удалось сохранить по любой причине, то ничего больше не делаем. Не портим файл пользователя нашей справкой.
						break;
					case QMessageBox::No:
						break;
					case QMessageBox::Cancel:
							return;
						break;
					default:
						break;
				}
		}
		this->setWindowTitle(QString(tr("Справка - ")) + defaultTitle);
		filestatus.reset();
		filestatus.setChanged(false);
		filestatus.setRO(true); //несмотря на то что мы по сути открываем файл из ресурсов программы, из-за флага read-only, программа не будет пытаться сохранить справку "внутрь программы"
		filestatus.setPath(":/src/txt/res/readme_"+lang+".txt");
		QFile file(filestatus.getPath());
			if(file.open(QIODevice::ReadOnly)){
				QByteArray ba = file.readAll();
				ui->plainTextEdit->setPlainText(ba.data());
				filestatus.setChanged(false);
				filestatus.setPath("");
			}
		actualizeForm();
}

void MainWindow::on_action_Russian_triggered()
{
		qApp->removeTranslator(&translator);
		lang = "ru";
		ui->retranslateUi(this); // без этой команды не обновляет интерфейс
		this->setWindowTitle(defaultTitle); // обнуляем заголовок на базовый, потому что я не сделал функцию, которая собирает заголовок (они задаются один раз при каком-то действии)
		// возможно добавлю в будущем
		ui->action_Russian->QAction::setEnabled(false);
		ui->action_Russian->setChecked(true);
		ui->action_English->QAction::setEnabled(true);
		ui->action_English->setChecked(false);
}

void MainWindow::on_action_English_triggered()
{
		translator.load(":/src/lang/res/QtLanguage_en.qm");
		qApp->installTranslator(&translator);
		lang = "en";
		ui->retranslateUi(this);
		this->setWindowTitle(defaultTitle);
		ui->action_Russian->QAction::setEnabled(true);
		ui->action_Russian->setChecked(false);
		ui->action_English->QAction::setEnabled(false);
		ui->action_English->setChecked(true);
}

void MainWindow::on_action_changeShortcuts_triggered()
	{
		// кнопка для вызова диалогового окна с полями клавиатурных сокращений
		dialogChangeShotcuts window(this,getShortcutsList());
		connect(&window,&dialogChangeShotcuts::sendList,this,&MainWindow::receiveShortcutsList);
		window.setModal(true);
		window.setWindowFlags(window.windowFlags() & ~Qt::WindowContextHelpButtonHint);
		window.exec();

	}

void MainWindow::initShortcutList()
	{
		// пересобирает лист с сокращениями, поочередно опрашивая интересующие нас кнопки
		shortcuts.clear();
		shortcuts.append(ui->action_NewFile->shortcut().toString());
		shortcuts.append(ui->action_Open->shortcut().toString());
		shortcuts.append(ui->action_OpenRO->shortcut().toString());
		shortcuts.append(ui->action_Save->shortcut().toString());
		shortcuts.append(ui->action_SaveAs->shortcut().toString());
		shortcuts.append(ui->action_Help->shortcut().toString());
		shortcuts.append(ui->action_quit->shortcut().toString());
	}

QStringList MainWindow::getShortcutsList()
	{
		return shortcuts;
	}

void MainWindow::receiveShortcutsList(QStringList newList)
	{
		// слот, который активируется кнопкой ПРИНЯТЬ в диалоговом окне
		ui->action_NewFile->setShortcut(newList.at(0));
		ui->action_Open->setShortcut(newList.at(1));
		ui->action_OpenRO->setShortcut(newList.at(2));
		ui->action_Save->setShortcut(newList.at(3));
		ui->action_SaveAs->setShortcut(newList.at(4));
		ui->action_Help->setShortcut(newList.at(5));
		ui->action_quit->setShortcut(newList.at(6));
		initShortcutList();
	}

void MainWindow::on_action_LightTheme_triggered()
{
		ui->action_LightTheme->QAction::setEnabled(false);
		ui->action_LightTheme->setChecked(true);
		ui->action_DarkTheme->QAction::setEnabled(true);
		ui->action_DarkTheme->setChecked(false);
		qApp->setStyleSheet("");
}

void MainWindow::on_action_DarkTheme_triggered()
{
		ui->action_LightTheme->QAction::setEnabled(true);
		ui->action_LightTheme->setChecked(false);
		ui->action_DarkTheme->QAction::setEnabled(false);
		ui->action_DarkTheme->setChecked(true);
		qApp->setStyleSheet("QMenuBar {background-color: #232323; color:white}"
							"QMenuBar::item:selected {background: #27609A}"
							"QMenu {background-color: #232323; color:white}"
							"QMenu::item:selected {background: #27609A}"
							"QMainWindow {background-color: #232323}"
							"QDialog {background-color: #333333}"
							"QLabel {color:white}"
							"QPlainTextEdit {background-color: #000000; color:white}"
							"QLineEdit {background-color: #000000; color:white}"
							"QPushButton {border: 1px solid #27609A; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #323232, stop: 1 #2c2c2c); color:white;min-height: 21px;padding-left: 25px;padding-right: 25px}"
							"QPushButton:hover {border: 2px solid #27609A; background-color: #353535; padding-left: 24px; padding-right: 24px}");
}

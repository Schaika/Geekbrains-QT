#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
// не разобрался как сделать, чтобы некоторые функции работали в режиме реального времени
// например флаг read-only может меняться пока файл открыт в программе, но программа об этом не узнает, если не нажать на кнопку или что-то подобное.
//Как сделать эту проверку автоматически?
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	{
		ui->setupUi(this);
		this->setWindowTitle(defaultTitle + QString(tr(" - Новый файл")));
		this->setWindowIcon(QIcon(":/src/ico/res/text-editor-logo.svg"));
	}

MainWindow::~MainWindow()
	{
		delete ui;
	}
int MainWindow::askUser(){
	//диалоговое окно, где пользователя спрашивают не хочет ли он сохранить изменения
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
void MainWindow::openDialog(){
		QString filename = QFileDialog::getOpenFileName(this, tr("Открыть файл..."), filestatus.hasPath() ? filestatus.getPath() : QDir::current().path(), filter); //если путь к файлу есть - открывает диалоговое окно в папке с текущим файлом, если нет - открывает окно в папке с программой
			if (filename.length()>0){
				filestatus.setPath(filename);
				filestatus.getExt(); //Получаем расширение файла. Расширение нигде не используется, заготовка на будущее
				QFile file(filename);
				QFileInfo info(file);
							filestatus.setRO(!info.isWritable());
							if (filestatus.isReadOnly()){
								this->setWindowTitle(defaultTitle + " (" + filename + ")" + QString(tr("  --  только для чтения")));
								//если файл только для чтения - в заголовке программмы рядом с путем будет соответсвубщая надпись
							}else{
								this->setWindowTitle(defaultTitle + " (" + filename + ")");
							}
					if(file.open(QIODevice::ExistingOnly | QIODevice::ReadOnly)){
						QByteArray bytedata = file.readAll();
						ui->plainTextEdit->setPlainText(bytedata.data());
						filestatus.setChanged(false);
					}
			}
	}
// saveAsDialog() - всего лишь выводит окно с выбором пути для сохранения файла, но ничего не сохраняет
bool MainWindow::saveAsDialog(){
		QString filename = QFileDialog::getSaveFileName(this, tr("Сохранить файл как..."), filestatus.hasPath() ? filestatus.getPath() : QDir::current().path() + QString(tr("/Новый файл")), filter);
		if (filename.length()>0){
			filestatus.reset();
			filestatus.setPath(filename);
			QString ext = filestatus.getExt();
			this->setWindowTitle(defaultTitle + " (" + filename + ")");
			return true;
		}else return false;
	}
// saveFile() проверяет можно ли писать в файл и есть ли путь к нему (в случае если файл новый)
bool MainWindow::saveFile(){
		if(filestatus.getPath().length()==0|| filestatus.isReadOnly() == true) if(!saveAsDialog()) return false;
		//возможно каждый раз при обращении к методу filestatus.isReadOnly() следовало бы проверять возможность писать в файл
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
		this->setWindowTitle(defaultTitle + QString(tr(" - Новый файл")));
		ui->plainTextEdit->clear();
		filestatus.setChanged(false);
	}
void MainWindow::on_action_NewFile_triggered()
{
	if(filestatus.hasChanges()){
		//проверка перед созданием нового файла, если текущий файл имеет изменения, то предлагаем сохранить их

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

void MainWindow::on_action_Open_triggered()
{
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
	exit(0); // пока не нашел функцию, которая позволяет перехватить (и даже отменить) закрытие программы, если нажат крестик или Alt+F4. Потому не стал добавлять проверку и предлагать сохранить файл на этой кнопке, иначе было бы странно.
}
void MainWindow::on_action_Help_triggered()
{

		// хотел сделать отдельную форму с файлом-справкой, но поскольку по заданию мы открываем ее из ресурсов программы, решил загружать ее прямо в поле текстового редактора
		// поскольку загружаем прямо в редактор, идет проверка, не изменен ли текущий файл и диалоговое окно с предложением сохранить изменения
		if(filestatus.hasChanges()){
					//поскольку это диалоговое окно немного отличается, оно написано заново. Используется один раз, потому не отдельной функцией
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
		this->setWindowTitle(defaultTitle + QString(tr(" - Справка")));
		filestatus.reset();
		filestatus.setChanged(false);
		filestatus.setRO(true); //несмотря на то что мы по сути открываем файл из ресурсов программы, из-за флага read-only, программа не будет пытаться сохранить справку "внутрь программы"
		filestatus.setPath(":/src/txt/res/readme.txt");
		QFile file(filestatus.getPath());
			if(file.open(QIODevice::ReadOnly)){
				QByteArray ba = file.readAll();
				ui->plainTextEdit->setPlainText(ba.data());
				filestatus.setChanged(false);
			}

}

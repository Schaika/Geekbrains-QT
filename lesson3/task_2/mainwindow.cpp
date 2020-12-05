#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
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

QStringList parse_currency(QString raw_html){
		QStringList result;

			//Ищем информацию о курсах валют
			qint32 last = 0;
			while (last!=-1) {
				int begin, end;
				last = raw_html.indexOf("rate__currency",last); //поиск по классу блока <div> // <div class="rate__currency svelte-1lhokyh">74.39</div>
				begin = raw_html.indexOf(">",last) + 1;
				end = raw_html.indexOf("<",begin);
				if (begin != -1 && end != -1){
					last = end;
					QString trim = raw_html.mid(begin,end-begin);
					result.append(trim);
				}

			}

		if (result.length()<2) throw -1; //если результатов меньше двух, то скорее всего что-то пошло совсем не так
		return result;
	}

QStringList parse_weather(QString raw_html){
		QStringList result;
		QStringList whatToSearch = {"weather__city","weather__temp","weather__description","weather__humidity"};
		//Ищем информацию о погоде
		qint32 last = 0;
		foreach (const QString str, whatToSearch){ //в самом HTML гораздо больше информации, которую можно было бы извлечь более умным алгоритмом. Мне было интересно посмореть как работает foreach
			int begin, end;
			last = raw_html.indexOf(str,last);
				if (last == -1) throw -1; //если ничего не найдено, выкидываем исключение
			begin = raw_html.indexOf(">",last) + 1;
			end = raw_html.indexOf("<",begin);
			if (begin != -1 && end != -1){
				last = end;
				QString trim = raw_html.mid(begin,end-begin);
				result.append(trim);
			}else{
				throw -1; //если не удалось вырезать строку, выкидываем исключение
			}
		}
		return result;
	}

void MainWindow::on_pushButton_loadHTML_released()
{
		QString filename = QFileDialog::getOpenFileName(this, "Open file", QDir::current().path(), "Webpage, HMTL files (*.html *.htm);;All files(*.*)");
		if (filename.isEmpty()) return;
		QFile HTML_file(filename);
		if(HTML_file.open(QIODevice::ReadOnly)){
			QByteArray bytes = HTML_file.readAll();
			QString HTML_raw = bytes.data();

			//поскольку обращение идет напрямую к индексам QStringList, чтобы не получать ошибки "index out of range"
			//я использовал исключения, т.к. мы никак не проверяем, что за файл нам дали на анализ и неизвестно найдем ли мы хоть что-нибудь


			//о курсах валют
			try {
				QStringList results = parse_currency(HTML_raw);
				ui->lineEdit_USD->setText(results[0]);
				ui->lineEdit_EUR->setText(results[1]);
			}  catch (int) {
					ui->lineEdit_USD->setText("Cannot Parse the File");
					ui->lineEdit_EUR->setText("Cannot Parse the File");
			}


			//о погоде
			try {
				ui->plainTextEdit->clear();
				QStringList weather = parse_weather(HTML_raw);
				ui->plainTextEdit->appendPlainText(weather[0]);
				ui->plainTextEdit->appendPlainText(weather[1]+", "+weather[2]);
				ui->plainTextEdit->appendPlainText(weather[3]);
			}  catch (int) {
				ui->plainTextEdit->appendPlainText(QString("Cannot Parse the File"));
			}

		}

}

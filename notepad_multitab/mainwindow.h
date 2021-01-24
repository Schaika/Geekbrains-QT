#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMdiArea>
#include <QTabBar>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QStyle>
#include <QFontDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QDateTime>
#include <QTranslator>
#include "qtextedit_custom.h"
#include "qmdisubwindo_custom.h"
#include "dialogshortcuts.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	QMdiArea* mdiArea = NULL;
	QTabBar* m_pMdiAreaTabBar = NULL;
private slots:
	void on_mdiArea_subWindowActivated(QMdiSubWindow *window);

	void on_actionAbout_triggered();

	void on_actionNew_file_triggered();

	void on_actionOpen_triggered();

	void textchanged();

	void on_actionLight_triggered();

	void on_actionDark_triggered();

	void closeTabEvent(QMdiSubWindo_custom*);
	void on_actionSave_triggered();

	void on_actionCopy_Text_Format_triggered();

	void on_actionApply_Text_Format_triggered();

	void on_actionCenter_triggered();

	void on_actionLeft_triggered();

	void on_actionRight_triggered();

	void on_actionOpen_force_read_only_triggered();

	void on_actionSave_as_triggered();

	void on_actionClose_triggered();

	void on_actionSave_all_triggered();

	void on_actionClose_all_triggered();

	void on_actionFont_triggered();

	void on_actionExit_triggered();

	void on_actionPrint_triggered();

	void on_actionEnglish_triggered();

	void on_actionRussian_triggered();

	void on_actionKey_Shortcuts_triggered();

private:
	void add_window(QString,QTextEdit_custom* obj = nullptr);
	void add_window();
	void setMainWindowTitle(QString);
	QTextCharFormat formatBuffer;
	QString projectName = QString("Text editor");
	QTranslator translator;
	QString language = "en_US";
	bool first = false;
	bool openDialog(QTextEdit_custom*, QString path = "");
	bool saveFile(QMdiSubWindo_custom*);
	bool saveAsDialog(QMdiSubWindo_custom*);
	QMdiSubWindo_custom* getCurrentQMdiSubWindow();
	QTextEdit_custom* getCurrentQTextEdit();
	int askUser();
	void openFileCheck();
private:
	Ui::MainWindow *ui;
protected:
	void closeEvent(QCloseEvent* event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void paintEvent(QPaintEvent *event) override;
};
#endif // MAINWINDOW_H

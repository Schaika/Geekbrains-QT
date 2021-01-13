#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCharFormat>
#include <QTranslator>
#include "filestatus.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();


private slots:
	void receiveShortcutsList(QStringList);
	void on_action_Help_triggered();
	void on_action_quit_triggered();
	void on_textEdit_textChanged();
	void on_action_NewFile_triggered();
	void on_action_Open_triggered();
	void on_action_Save_triggered();
	void on_action_SaveAs_triggered();
	void on_action_OpenRO_triggered();
	void on_action_Russian_triggered();
	void on_action_English_triggered();
	void on_action_changeShortcuts_triggered();

	void on_action_LightTheme_triggered();

	void on_action_DarkTheme_triggered();

	void on_action_Print_triggered();

	void on_action_Font_triggered();

	void on_action_CopyFormat_triggered();

	void on_action_ApplyFormat_triggered();

	void on_action_AlignCenter_triggered();

	void on_action_AlignLeft_triggered();

	void on_action_AlignRight_triggered();

private:
	QString defaultTitle = "Text editor";
	Ui::MainWindow *ui;
	QTranslator translator;
	QString lang = "ru";
	filestatus filestatus; // Класс filestatus следит за состоянием текущего файла, создается один раз
	QTextCharFormat formatBuffer;
	QStringList shortcuts;
	void initShortcutList();
	QStringList getShortcutsList();

	void openDialog();
	bool saveFile();
	bool saveAsDialog();
	void newFile();
	int askUser();
	void openFileCheck();
	void actualizeForm();
protected:
	void closeEvent(QCloseEvent* event) override;
};
#endif // MAINWINDOW_H
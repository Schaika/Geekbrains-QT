#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
	void on_buttonSolve_clicked();

	void on_lineA_editingFinished();

	void on_lineB_editingFinished();

	void on_lineC_editingFinished();

private:
	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

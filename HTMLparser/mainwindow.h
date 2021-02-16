#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QScrollArea>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>
#include "htmlhandler.h"
#include "framewgt.h"
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
private:
	HTMLhandler* handler;
	QScrollArea* scrollArea;
	QPushButton* searchbtn;
	QLineEdit* inputText;
	QSpinBox* imagesToShow;
	QGridLayout* imagesContainer;
	QWidget* placeholderWgtScrollArea;
	void paintEvent(QPaintEvent *event) override;
	void clearList();
	quint32 rows=0;
private slots:
	void doSearch();
};
#endif // MAINWINDOW_H

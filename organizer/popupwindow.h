#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QDialog>
#include <QSqlQueryModel>
namespace Ui {
	class popupWindow;
}

class popupWindow : public QDialog
{
	Q_OBJECT

public:
	explicit popupWindow(QWidget *parent = nullptr,QSqlQueryModel* model = nullptr);
	~popupWindow();
public slots:
	void updateModel(QSqlQueryModel* newModel);
private:
	Ui::popupWindow *ui;
};

#endif // POPUPWINDOW_H

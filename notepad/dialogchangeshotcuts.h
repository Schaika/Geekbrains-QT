#ifndef DIALOGCHANGESHOTCUTS_H
#define DIALOGCHANGESHOTCUTS_H

#include <QDialog>
namespace Ui {
	class dialogChangeShotcuts;
}

class dialogChangeShotcuts : public QDialog
{
	Q_OBJECT

public:
	explicit dialogChangeShotcuts(QWidget *parent = nullptr,QStringList list = {});
	~dialogChangeShotcuts();

private slots:

	void on_pushButton_discard_released();

	void on_pushButton_accept_released();
signals:
	void sendList(QStringList);
private:
	Ui::dialogChangeShotcuts *ui;
	QStringList *list;
};

#endif // DIALOGCHANGESHOTCUTS_H

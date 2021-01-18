#ifndef DIALOGSHORTCUTS_H
#define DIALOGSHORTCUTS_H

#include <QDialog>
#include <QGridLayout>
#include <QAction>
#include <QLabel>
#include <QKeySequenceEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QCloseEvent>
namespace Ui {
	class DialogShortcuts;
}

class DialogShortcuts : public QDialog
{
	Q_OBJECT

public:
	explicit DialogShortcuts(QList<QAction*>,QWidget *parent = nullptr);
	~DialogShortcuts();

private:
	bool safeToClose = false;
	bool changed = false;
	QGridLayout* gridLayout;
	QPushButton* ok;
	QPushButton* cancel;
	QList<QAction*> list;
	QList<QKeySequenceEdit*> keylist;
	Ui::DialogShortcuts *ui;
private slots:
	void Ok();
	void Cancel();
	void Change();
protected:
	void closeEvent(QCloseEvent *event) override;
};

#endif // DIALOGSHORTCUTS_H

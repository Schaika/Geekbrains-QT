#ifndef QMDISUBWINDO_CUSTOM_H
#define QMDISUBWINDO_CUSTOM_H

#include <QMdiSubWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <qtextedit_custom.h>
class QMdiSubWindo_custom : public QMdiSubWindow
{
	Q_OBJECT
public:
	QMdiSubWindo_custom(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
protected:
	void closeEvent(QCloseEvent *closeEvent);
signals:
	void closeTab(QMdiSubWindo_custom*);
};

#endif // QMDISUBWINDO_CUSTOM_H

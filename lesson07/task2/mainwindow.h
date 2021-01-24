#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include "customitem.h"
class MainWindow : public QGraphicsView
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
private slots:
	void removeObject(CustomItem*);
	void reDraw();
private:
	void zoomIn() { scale(1.2, 1.2); }
	void zoomOut() { scale(1 / 1.2, 1 / 1.2); }
		QGraphicsScene *scence;
		quint8 shape;
		QPoint lastPos;
protected:
		void mousePressEvent(QMouseEvent  *event) override;
		void wheelEvent(QWheelEvent *event) override;
		void keyPressEvent(QKeyEvent *keyEvent) override;
};
#endif // MAINWINDOW_H

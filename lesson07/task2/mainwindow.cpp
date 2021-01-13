#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QGraphicsView(parent)
	{
		srand(clock());
		scence = new QGraphicsScene(this);
		setScene(scence);
		shape = 0;
	}

MainWindow::~MainWindow()
	{
	}

void MainWindow::removeObject(CustomItem* obj)
	{
		obj->setVisible(false);
		scence->removeItem(obj);
		reDraw();
	}

void MainWindow::reDraw()
	{		
		scence->update();
		update();
	}


void MainWindow::mousePressEvent(QMouseEvent* event)
	{
		//qDebug() << sceneRect();
		//qDebug()<<this->width()<<this->height();
		if (itemAt(event->pos()) == NULL){
		if(event->button() == Qt::LeftButton)
		   {
			CustomItem *obj = new CustomItem(scence,shape,QBrush(QColor(rand() % 256, rand() % 256, rand() % 256)));
			connect(obj,SIGNAL(destroy(CustomItem*)),this,SLOT(removeObject(CustomItem*)));
			connect(obj, SIGNAL(reDraw()), this, SLOT(reDraw()));
			scence->addItem(obj);
			shape++;
			if (shape>2) shape=0;
		   }
		}else{
						QGraphicsView::mousePressEvent(event);
		}
	}

void MainWindow::wheelEvent(QWheelEvent* event)
	{
		 if (event->angleDelta().y() > 0) zoomIn();
		 if (event->angleDelta().y() < 0) zoomOut();
	}

void MainWindow::keyPressEvent(QKeyEvent* keyEvent)
	{
		if (keyEvent->key() == Qt::Key_Up){
			zoomIn();
		}
		if (keyEvent->key() == Qt::Key_Down){
			zoomOut();
		}
			reDraw();

	}

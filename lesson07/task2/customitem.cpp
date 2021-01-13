#include "customitem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QtMath>
CustomItem::CustomItem(QObject* parent,int p_myShape,QBrush p_Brush) : QObject(parent),QGraphicsItem()
	{
		x = 0;
		y = 0;
		myShape = static_cast<Geometry>(p_myShape);
		setBrush(p_Brush);
		setPos(0,0);
		moving = false;
		rotating = false;
		switch (myShape) {
		case RECTANGLE:
			boundX = 150;
			boundY = 150;
			break;
		case ELLIPS:
			boundX = 150;
			boundY = 120;
			break;
		case STAR:
			boundX = 160;
			boundY = 136;
			break;
		}
		setTransformOriginPoint(QPoint(boundX/2,boundY/2));
	}

CustomItem::~CustomItem()
	{

	}


void CustomItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
	{
		painter->setBrush(brush);
		switch (myShape) {
		case RECTANGLE:
			painter->drawRect(x, y, 150, 150);
			break;
		case ELLIPS:
			painter->drawEllipse(x, y, 150, 120);
			break;
		case STAR:
			QPolygon poly;
			poly << QPoint(80+x, 148+y) << QPoint(98+x, 94+y) << QPoint(160+x, 94+y) << QPoint(110+x, 58+y) << QPoint(130+x, 0+y) << QPoint(80+x, 36+y) << QPoint(30+x, 0+y) << QPoint(50+x, 58+y) << QPoint(0+x, 94+y) << QPoint(62+x, 94+y) << QPoint(80+x, 148+y);
			painter->drawPolygon(poly);
			break;
		}
		Q_UNUSED(option)
		Q_UNUSED(widget)
	}

QRectF CustomItem::boundingRect() const
	{
		if (myShape==STAR) return QRect(x,y,boundX,148);
		return QRectF(x,y, boundX, boundY);
	}

void CustomItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
	{
		if(event->button() == Qt::RightButton){
				emit destroy(this);
		   }
		if (event->button() == Qt::LeftButton){
			moving = true;
			bpoint = event->pos().toPoint();
			}
		if (event->button() == Qt::MiddleButton)
		{
			rotating = true;
			lastAngle = rotation();
			setRotation(0);
			setTransformOriginPoint(QPoint(x,y)+QPoint(boundX/2,boundY/2));
			setRotation(lastAngle);
			bpoint = event->scenePos().toPoint()-QPoint(boundX/2,boundY/2);
		}
		//qDebug() << rotating << moving << QPoint(x,y);
	}

void CustomItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
	{
		Q_UNUSED(event);
			moving = false;
			rotating = false;
			emit reDraw();
			//qDebug() << rotating << moving << QPoint(x,y);
	}

void CustomItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
	{
		if (moving)
		{
			prepareGeometryChange();
			QPoint p = event->pos().toPoint() - bpoint;
			x += p.x();
			y += p.y();
			bpoint = event->pos().toPoint();
			emit reDraw();
			//qDebug() << rotating << moving << QPoint(x,y);
		}
		if (rotating)
		{
			prepareGeometryChange();
			QPointF p = event->scenePos().toPoint() - transformOriginPoint();
			qreal angle = qRadiansToDegrees( qAcos( ( p.x()*bpoint.x() + p.y()*bpoint.y() ) / ( qSqrt( p.x()*p.x() + p.y()*p.y() ) * qSqrt( bpoint.x()*bpoint.x() + bpoint.y()*bpoint.y() ) ) ) );
			qreal determ = p.x()*bpoint.y()-p.y()*bpoint.x();
			bool sign = (determ > 0) ? 1 : ((x < 0) ? -1 : 0);
				if (sign) angle = 360-angle;
			qDebug()<<angle;
			//qDebug()<<bpoint<<p;
			qDebug() << rotating << moving << QPoint(x,y);
			setRotation(angle+lastAngle);
			emit reDraw();
		}
	}

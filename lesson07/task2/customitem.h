#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QContextMenuEvent>
#include <QBrush>
#include <QDebug>
class CustomItem : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
	explicit CustomItem(QObject *parent = nullptr, int p_myShape = Geometry::RECTANGLE,QBrush p_brush = QBrush());
	~CustomItem();
	void setBrush(QBrush brush) {this->brush = brush; emit reDraw();}
signals:
	void reDraw();
	void destroy(CustomItem*);
private:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	QRectF boundingRect() const override;
	enum Geometry {RECTANGLE, ELLIPS,STAR};
	Geometry myShape;
	int x,y;
	quint8 boundX,boundY;
	bool moving;
	bool rotating;
	QPoint bpoint;
	qreal lastAngle;
	QBrush brush;
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent  *event)  override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent  *event)  override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CUSTOMITEM_H

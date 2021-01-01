#ifndef FISHVIEW_H
#define FISHVIEW_H

#include <QGraphicsItem>

class FishView : public QGraphicsItem
{
public:
    FishView();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
    void advance(int step);

private:
    qreal angle;
    qreal speed;
    qreal mouseEyeDirection;
    QColor color;
};

#endif

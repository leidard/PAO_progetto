//#include "fishview.hpp"
//#include "acquarioview.hpp"

//#include <QPaintEvent>
//#include <QPainter>
//#include <QResizeEvent>

//#include "deepptr.hpp"
//#include "fish.hpp"
//#include "vect2d.hpp"

//void FishView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
//    painter.setRenderHint(QPainter::Antialiasing);

//    auto fish = controller->getAllFish();
//    for (auto &f : fish) {
//        Vect2D pos = f->getPosition();
//        Vect2D vel = f->getVelocity().setMagnitude(15);
//        Vect2D left = Vect2D::rotate(vel, -2.5).setMagnitude(20);
//        Vect2D right = Vect2D::rotate(vel, 2.5).setMagnitude(20);
//        Vect2D fut = pos + vel;
//        Vect2D futl = pos + left;
//        Vect2D futr = pos + right;
//        // painter.drawRect(pos.x()-10, pos.y()-10, 20, 20);
//        // painter.drawLine(pos.x(), pos.y(), fut.x(), fut.y());
//        // painter.drawLine(futl.x(), futl.y(), pos.x(), pos.y());
//        // painter.drawLine(futr.x(), futr.y(), pos.x(), pos.y());
//        // painter.drawLine(futr.x(), futr.y(), fut.x(), fut.y());
//        QPointF* points = new QPointF[3];
//        points[0] = QPointF(futl.x(), futl.y());
//        points[1] = QPointF(futr.x(), futr.y());
//        points[2] = QPointF(fut.x(), fut.y());
//        painter.setBrush(QBrush(QColor("red")));
//        painter.drawPolygon(points, 3);
//    }

//    // Body
//    painter->setBrush(color);
//    painter->drawEllipse(-10, -20, 20, 40);

//    // Eyes
//    painter->setBrush(Qt::white);
//    painter->drawEllipse(-10, -17, 8, 8);
//    painter->drawEllipse(2, -17, 8, 8);

//    // Nose
//    painter->setBrush(Qt::black);
//    painter->drawEllipse(QRectF(-2, -22, 4, 4));

//    // Pupils
//    painter->drawEllipse(QRectF(-8.0 + mouseEyeDirection, -17, 4, 4));
//    painter->drawEllipse(QRectF(4.0 + mouseEyeDirection, -17, 4, 4));

//    // Ears
//    painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::darkYellow : Qt::red);
//    painter->drawEllipse(-17, -12, 16, 16);
//    painter->drawEllipse(1, -12, 16, 16);

//    // Tail
//    QPainterPath path(QPointF(0, 20));
//    path.cubicTo(-5, 22, -5, 22, 0, 25);
//    path.cubicTo(5, 27, 5, 32, 0, 30);
//    path.cubicTo(-5, 32, -5, 42, 0, 35);
//    painter->setBrush(Qt::NoBrush);
//    painter->drawPath(path);
//}

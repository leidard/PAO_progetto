#include "acquarioview.hpp"

#include <QPaintEvent>
#include <QPainter>
#include <QResizeEvent>

#include "deepptr.hpp"
#include "fish.hpp"
#include "vect2d.hpp"

AcquarioView::AcquarioView(QWidget *parent) : QWidget(parent) {
}

void AcquarioView::setController(Controller *c) {
    controller = c;
}

void AcquarioView::resizeEvent(QResizeEvent *event) {
    QSize s = event->size();
    controller->resize(s.width(), s.height());
}

#include <QPointF>
#include <iostream>
#include <QColor>
#include <QBrush>
void AcquarioView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    auto fish = controller->getAllFish();
    for (auto &f : fish) {
        Vect2D pos = f->getPosition();
        Vect2D vel = f->getVelocity().setMagnitude(15);
        Vect2D left = Vect2D::rotateDeg(vel, -2.5).setMagnitude(20);
        Vect2D right = Vect2D::rotateDeg(vel, 2.5).setMagnitude(20);
        Vect2D fut = pos + vel;
        Vect2D futl = pos + left;
        Vect2D futr = pos + right;
        // painter.drawRect(pos.x()-10, pos.y()-10, 20, 20);
        // painter.drawLine(pos.x(), pos.y(), fut.x(), fut.y());
        // painter.drawLine(futl.x(), futl.y(), pos.x(), pos.y());
        // painter.drawLine(futr.x(), futr.y(), pos.x(), pos.y());
        // painter.drawLine(futr.x(), futr.y(), fut.x(), fut.y());
        QPointF* points = new QPointF[3];
        points[0] = QPointF(futl.x(), futl.y());
        points[1] = QPointF(futr.x(), futr.y());
        points[2] = QPointF(fut.x(), fut.y());
        painter.setBrush(QBrush(QColor("red")));
        painter.drawPolygon(points, 3);
    }

    //controller->getFish();
    //controller->getVegetali();
}

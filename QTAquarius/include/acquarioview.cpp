#include "acquarioview.h"

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


#include <iostream>
void AcquarioView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    auto fish = controller->getAllFish();
    for (auto &f : fish) {
        Vect2D v = f->getPosition();
        painter.drawRect(v.x(), v.y(), 20, 20);
    }

    //controller->getFish();
    //controller->getVegetali();
}

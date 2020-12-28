#include "view.hpp"

#include "controller.hpp"

FishView::FishView() : controller(nullptr) {}

void FishView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->drawText(0, 0, "Alpha");
    QGraphicsPixmapItem::paint(painter, option, widget);  // do default things (draw the pixmap)
}
void FishView::setController(Controller::FishController* c) {
    controller = c;
    // connect things
}

void FishView::advance(int phase) {
    setPos(mapToParent(controller->getPosition()));
    setRotation(controller->getRotation());
}
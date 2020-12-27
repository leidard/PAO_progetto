#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPainter>

#ifndef ITEMVIEW_H
#define ITEMVIEW_H

class Controller {
   public:
    class VegetaleController;
    class FishController;
};

class FishView : public QGraphicsPixmapItem {
   public:
    FishView();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    void setController(Controller::FishController*);

   protected:
    void advance(int) override;

   private:
    Controller::FishController* controller;
};

class VegetaleView : public QGraphicsPixmapItem {
   public:
    VegetaleView();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    void setController(Controller::VegetaleController*);

   private:
    Controller::VegetaleController* controller;
};

// the

#endif
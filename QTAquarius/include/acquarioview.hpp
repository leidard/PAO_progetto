#include "controller.hpp"
#include "fishinfoview.hpp"

#ifndef ACQUARIOVIEW_H
#define ACQUARIOVIEW_H
#include <QBrush>
#include <QCloseEvent>
#include <QColor>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QPointF>
#include <QPointer>
#include <QPushButton>
#include <QResizeEvent>
#include <QString>
#include <QWidget>
#include <iostream>

class AcquarioView : public QWidget {
    Q_OBJECT
   private:
    Controller* controller;
    FishInfoView* infoView;

   public:
    explicit AcquarioView(QWidget* parent = nullptr);
    void setController(Controller* c);
    void resizeEvent(QResizeEvent* event) override;

   protected:
    void paintEvent(QPaintEvent* event) override;

   private slots:
    void openInfo();
};

#endif  // ACQUARIOVIEW_H

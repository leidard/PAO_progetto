#include "controller.hpp"
#include "fishinfoview.hpp"

#ifndef ACQUARIOVIEW_H
#define ACQUARIOVIEW_H
#include <QBrush>
#include <QColor>
#include <QPointF>

#include <QCloseEvent>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QPointer>
#include <QPushButton>
#include <QResizeEvent>
#include <QString>
#include <QWidget>
#include <QMouseEvent>
#include <iostream>

class AcquarioView : public QWidget {
    Q_OBJECT
   private:
    Controller* controller;
    FishInfoView* infoView;
    QVBoxLayout* layout;
    QMenuBar* menuBar;
    QMenu* file;
    QMenu* strumenti;
    QAction* pausariprendi;
    QActionGroup* strumentiOptions;
    QAction* aggiungiPreda;
    QAction* aggiungiPredatore;
    QAction* infoPesci;
    QAction* fileSalva;
    QAction* fileCarica;
    bool drawingPreda;
    bool drawingPredatore;
    bool pausa;

    //    QPointer<QAction> fileSalva;
    //    QPointer<QAction> fileCarica;

   public:
    explicit AcquarioView(QWidget* parent = nullptr);
    // void buildMenu
    void setController(Controller* c);
    void resizeEvent(QResizeEvent* event) override;

   protected:
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

   private slots:
    void openInfo();
    void drawPreda();
    void drawPredatore();
    void stopGo();

};

#endif  // ACQUARIOVIEW_H

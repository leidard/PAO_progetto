#include <QWidget>

#include "controller.hpp"
#include "fishinfoview.hpp"

#ifndef ACQUARIOVIEW_H
#define ACQUARIOVIEW_H

class Controller;
class FishInfoView;
class QVBoxLayout;
class QMenuBar;
class QMenu;
class QAction;
class QActionGroup;
class QResizeEvent;
class QMouseEvent;
class QPaintEvent;

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

   public:
    explicit AcquarioView(QWidget* parent = nullptr);
    void setController(Controller* c);

   protected:
    void resizeEvent(QResizeEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent*) override;

   private slots:
    void openInfo();
    void drawPreda();
    void drawPredatore();
    void stopGo();
};

#endif

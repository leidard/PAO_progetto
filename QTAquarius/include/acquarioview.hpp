#include <QWidget>

#include "controller.hpp"

#ifndef ACQUARIOVIEW_H
#define ACQUARIOVIEW_H

class Controller;
class OrganismoInfoView;
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
   public:
    enum Tool {
        NIENTE,
        TONNO,
        SARDINA,
    };

   private:
    Controller* controller;
    OrganismoInfoView* infoView;
    QVBoxLayout* layout;
    QMenuBar* menuBar;
    QMenu* file;
    QMenu* strumenti;
    QAction* pausariprendi;
    QActionGroup* strumentiOptions;
    QAction* aggiungiSardina;
    QAction* aggiungiTonno;
    QAction* infoPesci;
    QAction* fileSalva;
    QAction* fileCarica;
    Tool drawing;
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
    void drawSardina();
    void drawTonno();
    void stopGo();
};

#endif

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
    static const Vect2D vertex[3];
    static const double minScale;
    static const double maxScale;
    static const unsigned int minColor;
    static const unsigned int maxColor;

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

    unsigned int minVal;
    unsigned int maxVal;

   public:
    explicit AcquarioView(QWidget* parent = nullptr);
    bool isInfoViewVisible() const;
    void setController(Controller* c);

   protected:
    void resizeEvent(QResizeEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent*) override;
    static void shader(const Vect2D* v, unsigned int s, const Vect2D& position, double angle, QPointF* dest, double scale);

   private slots:
    void openInfo();
    void drawSardina();
    void drawTonno();
    void stopGo();
};

#endif

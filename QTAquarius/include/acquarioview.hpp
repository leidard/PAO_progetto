#include <QWidget>
#include "organismoinfoview.hpp"
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
    static const Vect2D vertex[3];
    static const double minScale;
    static const double maxScale;
    static const unsigned int minColor;
    static const unsigned int maxColor;

   private:
    Controller* controller;
    QVBoxLayout* layout;
    QMenuBar* menuBar;
    QMenu* file;
    QMenu* aggOrg;
    QMenu* simulazione;
    QAction* pausariprendi;
    QAction* autorespawn;
    QActionGroup* strumentiOptions;
    QAction* aggiungiSardina;
    QAction* aggiungiTonno;
    QAction* aggiungiPhytoplankton;
    QAction* infoPesci;
    QAction* fileSalva;
    QAction* fileCarica;
    QAction* fileRinomina;
    bool pausa;

    unsigned int minVal;
    unsigned int maxVal;

   public:
    explicit AcquarioView(QWidget* parent = nullptr);
    void setController(Controller* c);

   protected:
    void resizeEvent(QResizeEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent*) override;
    static void shader(const Vect2D* v, unsigned int s, const Vect2D& position, double angle, QPointF* dest, double scale);

   private slots:
    void stopGo();
    void save();
    void load();
    void rename();
    void closeEvent(QCloseEvent *event);
};

#endif

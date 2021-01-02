#include <QObject>
#include <QPointF>
#include <QTimer>

#include "deepptr.hpp"
#include "vect2d.hpp"
#include "vector.hpp"

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Fish;
class Aquarius;
class AcquarioView;

class Controller : public QObject {
    Q_OBJECT

   private:
    QTimer* _timer;
    Aquarius* _model;
    AcquarioView* _view;

   public:
    explicit Controller(QObject* parent = nullptr);
    ~Controller();

    void setModel(Aquarius*);
    void setView(AcquarioView*);

    const Vector<DeepPtr<Fish>>& getAllFish();

    /*
        io farei un setTool 
        dove si imposta lo strumento tra 

        - Crea Predatore, 
        - Crea Preda, 
        - Crea cibo, 
        - NULL

        dopo di che uno slot unico riceve il click
    */

    /*
        Evento: [ Elimina ]
        L'evento elimina sará gestito da uno handler/slot diverso
        L'evento arriva da uno specifico item che ha rilevato l'evento mouseHover + mouseDown 
                    (rilevare quindi il click e trascinamento)
    */

    void resize(int width, int height);

    void addPredatore(const Vect2D&);  // click
    void addPreda(const Vect2D&);      // click
    void remFish();                    // click

   public slots:
    void advance();
    void start();
    void stop();

    // void clickView(QPointF);
};

#endif

#include <QGraphicsScene>
#include <QObject>

#include "deepptr.hpp"
#include "vector.hpp"
#include "view.hpp"

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Vegetale;
class Fish;
class Aquarius;
class FishView;
class VegetaleView;

class Controller : public QObject {
    Q_OBJECT
   public:
    class FishController;
    class VegetaleController;

   private:
    Vector<Controller::FishController*> fishControllers;
    Vector<Controller::VegetaleController*> vegetaleControllers;

    QTimer* _timer;
    Aquarius* _model;
    QGraphicsView* _view;
    QGraphicsScene* _scene;

   public:
    class FishController {
       private:
        Fish* _fishmodel;  // deep ptr could be useful??
        FishView* _fishview;

       public:
        FishController();
        ~FishController();        // deepptr
        FishController* clone();  // deepptr

        void setModel(Fish*);
        void setView(FishView*);

        FishView* view();

        QPointF getPosition() const;
        double getRotation() const;
    };
    class VegetaleController {
       private:
        Vegetale* _vegmodel;  // deep ptr could be useful??
        VegetaleView* _vegview;

       public:
        VegetaleController(Vegetale*, QGraphicsScene*);
        ~VegetaleController();        // deepptr
        VegetaleController* clone();  // deepptr

        void setModel(Vegetale*);
        void setView(VegetaleView*);

        VegetaleView* view();

        QPointF getPosition() const;
    };
    explicit Controller(QObject* parent = nullptr);
    ~Controller();

    void setModel(Aquarius*);
    void setView(QGraphicsView*);

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

    void addPredatore();  // click
    void addPreda();      // click
    void remFish();       // click
    void remVegetale();   // click

   public slots:
    void advance();
    void start();
    void stop();
    
    
    
    void clickView(QPointF);
};

#endif
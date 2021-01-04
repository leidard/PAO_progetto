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
    unsigned int infoviewpos;

   public:
    explicit Controller(QObject* parent = nullptr);
    ~Controller();

    void setModel(Aquarius*);
    void setView(AcquarioView*);

    Vector<DeepPtr<Fish>>& getAllFish();

    void resize(int width, int height);

    void addPredatore(const Vect2D&);  // click
    void addPreda(const Vect2D&);      // click

    // infoview
    unsigned int getVectorSize();
    unsigned int getPosition();
    bool hasNext();
    bool hasPrev();
    void next();
    void prev();
    const Fish* getCurrent();

    void updateName(const std::string&);

   public slots:
    void advance();
    void start();
    void stop();

    // void clickView(QPointF);
};

#endif

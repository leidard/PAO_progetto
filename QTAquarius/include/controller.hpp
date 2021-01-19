#include <QObject>

#include "deepptr.hpp"
#include "vect2d.hpp"
#include "vector.hpp"

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Organismo;
class QTimer;
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

    const Vector<DeepPtr<Organismo>>& getAllOrganismi();

    void resize(int width, int height);

    void addTonno(const Vect2D&);    // click
    void addSardina(const Vect2D&);  // click

    // infoview
    bool isInfoViewVisible();
    unsigned int getVectorSize();
    unsigned int getPosition();
    bool hasNext();
    bool hasPrev();
    void next();
    void prev();
    void reset();
    const Organismo* getCurrent();

    void updateNameOfCurrent(const std::string&);

   public slots:
    void advance();
    void start();
    void stop();
};

#endif

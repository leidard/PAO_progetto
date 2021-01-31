#include <QObject>

#include "deepptr.hpp"
#include "vect2d.hpp"
#include "vector.hpp"
#include "saverloader.hpp"

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
    SaverLoader* _saver;

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
    void addPhytoplankton(const Vect2D&);  // click

    //
    const std::string& getAquariusName() const;

    // simulation

    bool isRunning() const;
    bool isAutoRespawnEnabled() const;
    void toggleAutoRespawn() const;

    // infoview
    bool isInfoViewVisible() const;
    unsigned int getVectorSize() const;
    unsigned int getPosition() const;
    bool hasNext() const;
    bool hasPrev() const;
    void next();
    void prev();
    void reset();
    const Organismo* getCurrent();

    void updateNameOfCurrent(const std::string&);

    void saveData(QString*) const;

   public slots:
    void advance();
    void start();
    void stop();
};

#endif

#include <QObject>

#include "deepptr.hpp"
#include "vect2d.hpp"
#include "vector.hpp"
#include "io.hpp"

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Organismo;
class QTimer;
class Aquarius;
class AcquarioView;
class QMouseEvent;

class Controller : public QObject {
    Q_OBJECT

   public:
    enum Tool {
        NIENTE,
        TONNO,
        SARDINA,
        PHYTOPLANKTON
    };
    explicit Controller(QObject* parent = nullptr);
    ~Controller();

    void setModel(Aquarius*);
    void setView(AcquarioView*);

    const Vector<DeepPtr<Organismo>>& getAllOrganismi();

    void resize(int width, int height);

    void addTonno(const Vect2D&);    // click
    void addSardina(const Vect2D&);  // click
    void addPhytoplankton(const Vect2D&);  // click

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

    void loadData(const std::string&);
    void saveData(const std::string&) const;

    void mouseReleaseEvent(QMouseEvent*);

    private:
     QTimer* _timer;
     Aquarius* _model;
     AcquarioView* _view;
     IO* _saver;
     Tool drawing;
     unsigned int infoviewpos;


   public slots:
    void advance();
    void start();
    void stop();
    void drawSardina();
    void drawTonno();
    void drawPhytoplankton();
};

#endif

#include <QObject>

#include "deepptr.hpp"
#include "infocontroller.hpp"
#include "io.hpp"
#include "vect2d.hpp"
#include "vector.hpp"

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Organismo;
class QTimer;
class Aquarius;
class AcquarioView;
class QMouseEvent;
class InfoView;

class Controller : public QObject {
    Q_OBJECT

public:
    enum Tool { NIENTE, TONNO, SARDINA, PHYTOPLANKTON };

private:
    QTimer* _timer;
    Aquarius* _model;
    AcquarioView* _view;
    InfoController* _infocontroller;
    Tool _tool;
    unsigned int infoviewpos;

public:
    explicit Controller(QObject* parent = nullptr);
    ~Controller();

    void setModel(Aquarius*);
    void setView(AcquarioView*);
    void setInfoView(InfoView*);
    void setInfoController(InfoController*);

    const Vector<DeepPtr<Organismo>>& getAllOrganismi();

    void resize(int width, int height);

    // drawing
    void setTool(Controller::Tool);
    void useTool(const Vect2D&);
    void addTonno(const Vect2D&);
    void addSardina(const Vect2D&);
    void addPhytoplankton(const Vect2D&);

    const std::string& getAquariusName() const;
    void setAquariusName(const std::string&);

    // simulation
    bool isRunning() const;
    bool isAutoRespawnEnabled() const;

    // infoview

    void openInfo();
    bool isInfoViewVisible() const;
    Organismo* getInfoCurrent() const;

    // load/save

    void loadAquarius(const std::string&);
    void saveAquarius(const std::string&) const;

public slots:
    void advance();
    void start();
    void stop();
    void drawSardina();
    void drawTonno();
    void drawPhytoplankton();
    void toggleRunning();
    void toggleAutoRespawn();
};

#endif

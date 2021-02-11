#include "controller.hpp"

#include <QMouseEvent>
#include <QTimer>

#include "acquarioview.hpp"
#include "aquarius.hpp"
#include "sardina.hpp"
#include "phytoplankton.hpp"
#include "tonno.hpp"

Controller::Controller(QObject* parent) : QObject(parent), _timer(new QTimer()), _model(nullptr), _view(nullptr) {
    connect(_timer, SIGNAL(timeout()), this, SLOT(advance()));
}

Controller::~Controller() { delete _timer; }

void Controller::setModel(Aquarius* model) {
    _model = model;
    _infocontroller->setModel(model);
}

void Controller::setView(AcquarioView* view) {
    _view = view;
    connect(_timer, SIGNAL(timeout()), _view, SLOT(update()));
}

void Controller::setInfoController(InfoController* ic) { _infocontroller = ic; }

void Controller::setInfoView(InfoView* view) { _infocontroller->setView(view); }

const Vector<DeepPtr<Organismo>>& Controller::getAllOrganismi() {
    return _model->getAllOrganismi();
}

void Controller::addTonno(const Vect2D& position) {
    _model->addOrganismo(new Tonno(position));
}

void Controller::addSardina(const Vect2D& position) {
    _model->addOrganismo(new Sardina(position));
}

void Controller::addPhytoplankton(const Vect2D& position) {
    _model->addOrganismo(new Phytoplankton(position));
}

void Controller::resize(int width, int height) {
    _model->setSize(width, height);
}

const std::string& Controller::getAquariusName() const {
    return _model->getName();
};

void Controller::setAquariusName(const std::string& name) {
    _model->setName(name);
}

// simulazione
bool Controller::isRunning() const { return _timer->isActive(); }
bool Controller::isAutoRespawnEnabled() const {
    return _model->isAutoRespawnEnabled();
}
void Controller::toggleAutoRespawn() {
    if (_model->isAutoRespawnEnabled())
        _model->disableAutoRespawn();
    else
        _model->enableAutoRespawn();
}
void Controller::toggleRunning() {
    if (isRunning())
        stop();
    else
        start();
}

// infoview

void Controller::openInfo() { _infocontroller->show(); }

bool Controller::isInfoViewVisible() const {
    return _infocontroller->isVisible();
}

Organismo* Controller::getInfoCurrent() const {
    return _infocontroller->getCurrent();
}

//// ------------

void Controller::loadAquarius(const std::string& filename) {
    (new IO())->load(_model, filename);
}

void Controller::saveAquarius(const std::string& filename) const {
    (new IO())->save(_model, filename);
}

// slots
void Controller::advance() { _model->advance(); }

void Controller::start() {
    if (!_timer->isActive()) _timer->start(20);
}

void Controller::stop() {
    if (_timer->isActive()) _timer->stop();
}

// drawing
void Controller::useTool(const Vect2D& pos) {
    switch (_tool) {
    case Tool::TONNO:
        addTonno(pos);
        break;
    case Tool::SARDINA:
        addSardina(pos);
        break;
    case Tool::PHYTOPLANKTON:
        addPhytoplankton(pos);
        break;
    default:
        break;
    }
}

void Controller::drawSardina() {
    if (_tool == Tool::SARDINA)
        _tool = Tool::NIENTE;
    else
        _tool = Tool::SARDINA;
}

void Controller::drawTonno() {
    if (_tool == Tool::TONNO)
        _tool = Tool::NIENTE;
    else
        _tool = Tool::TONNO;
}

void Controller::drawPhytoplankton() {
    if (_tool == Tool::PHYTOPLANKTON)
        _tool = Tool::NIENTE;
    else
        _tool = Tool::PHYTOPLANKTON;
}

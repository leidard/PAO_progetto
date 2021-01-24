#include "controller.hpp"

#include <QTimer>

#include "acquarioview.hpp"
#include "aquarius.hpp"
#include "sardina.hpp"
#include "tonno.hpp"

Controller::Controller(QObject* parent) : QObject(parent), _timer(new QTimer()), _model(nullptr), _view(nullptr), infoviewpos(0) {
    connect(_timer, SIGNAL(timeout()), this, SLOT(advance()));
}

Controller::~Controller() {
    delete _timer;
}

void Controller::setModel(Aquarius* model) {
    _model = model;
}

void Controller::setView(AcquarioView* view) {
    _view = view;
    connect(_timer, SIGNAL(timeout()), _view, SLOT(update()));
}

const Vector<DeepPtr<Organismo>>& Controller::getAllOrganismi() {
    return _model->getAllOrganismi();
}

void Controller::addTonno(const Vect2D& position) {
    _model->addOrganismo(new Tonno(position));
}

void Controller::addSardina(const Vect2D& position) {
    _model->addOrganismo(new Sardina(position));
}

void Controller::resize(int width, int height) {
    _model->setSize(width, height);
}


const std::string& Controller::getAquariusName() const {
    return _model->getName();
};

// simulazione

bool Controller::isRunning() const { return _timer->isActive(); }
bool Controller::isAutoRespawnEnabled() const { return _model->isAutoRespawnEnabled(); }
void Controller::toggleAutoRespawn() const { if (_model->isAutoRespawnEnabled()) _model->disableAutoRespawn(); else _model->enableAutoRespawn();}


// InfoView part

unsigned int Controller::getVectorSize()const {
    return _model->getAllOrganismi().size();
}

unsigned int Controller::getPosition()const {
    return infoviewpos;
}

bool Controller::hasNext() const {
    return infoviewpos < _model->getAllOrganismi().size() - 1;
}

bool Controller::hasPrev() const  {
    return infoviewpos > 0;
}

void Controller::next() {
    if (hasNext())
        infoviewpos++;
}

void Controller::prev() {
    if (hasPrev())
        infoviewpos--;
}

void Controller::reset() {
    unsigned int last = _model->getAllOrganismi().size() - 1;
    if (infoviewpos > last) infoviewpos = last;
}

const Organismo* Controller::getCurrent() {
    if (infoviewpos < _model->getAllOrganismi().size())
        return _model->getAllOrganismi()[infoviewpos].get();
    else
        return nullptr;
}

void Controller::updateNameOfCurrent(const std::string& name) {
    if (infoviewpos < _model->getAllOrganismi().size())
        _model->getAllOrganismi()[infoviewpos]->setName(name);
}

// slots
void Controller::advance() {
    _model->advance();
}

void Controller::start() {
    _timer->start(20);
}

void Controller::stop() {
    _timer->stop();
}

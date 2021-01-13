#include "controller.hpp"

#include <QTimer>

#include "acquarioview.hpp"
#include "aquarius.hpp"
#include "pescevolante.hpp"
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

Vector<DeepPtr<Organismo>>& Controller::getAllFish() {
    return _model->getAllFish();
}

void Controller::addTonno(const Vect2D& position) {
    _model->addFish(new Tonno(position, "paolo"));
}

void Controller::addPesceVolante(const Vect2D& position) {
    _model->addFish(new PesceVolante(position, "paolo"));
}

void Controller::resize(int width, int height) {
    _model->setSize(width, height);
}

// InfoView part

unsigned int Controller::getVectorSize() {
    return _model->getAllFish().size();
}

unsigned int Controller::getPosition() {
    return infoviewpos;
}

bool Controller::hasNext() {
    return infoviewpos < _model->getAllFish().size() - 1;
}

bool Controller::hasPrev() {
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
    unsigned int last = _model->getAllFish().size() - 1;
    if (infoviewpos > last) infoviewpos = last;
}

const Organismo* Controller::getCurrent() {
    if (infoviewpos < _model->getAllFish().size())
        return _model->getAllFish()[infoviewpos].get();
    else
        return nullptr;
}

void Controller::updateName(const std::string& name) {
    if (infoviewpos < _model->getAllFish().size())
        _model->getAllFish()[infoviewpos]->setName(name);
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

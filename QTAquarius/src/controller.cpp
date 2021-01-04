#include "controller.hpp"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QPointF>
#include <QTimer>

#include "acquarioview.hpp"
#include "aquarius.hpp"
#include "deepptr.hpp"
#include "fish.hpp"
#include "preda.hpp"
#include "predatore.hpp"
#include "vect2d.hpp"
#include "vector.hpp"

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

Vector<DeepPtr<Fish>>& Controller::getAllFish() {
    return _model->getAllFish();
}

void Controller::addPredatore(const Vect2D& position) {
    _model->addFish(new Predatore(position, "paolo"));
}

void Controller::addPreda(const Vect2D& position) {
    _model->addFish(new Preda(position, "paolo"));
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

const Fish* Controller::getCurrent() {
    if (infoviewpos >= 0 && infoviewpos < _model->getAllFish().size())
        return _model->getAllFish()[infoviewpos].get();
    else
        return nullptr;
}

void Controller::updateName(const std::string& name) {
    if (infoviewpos >= 0 && infoviewpos < _model->getAllFish().size())
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

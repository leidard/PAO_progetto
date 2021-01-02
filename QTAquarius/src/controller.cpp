#include "controller.hpp"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QPointF>
#include <QTimer>

#include "predatore.hpp"
#include "aquarius.hpp"
#include "deepptr.hpp"
#include "fish.hpp"
//#include "middlewares/fishcreator.hpp"
//#include "middlewares/foodcreator.hpp"
#include "preda.hpp"
#include "predatore.hpp"
#include "vect2d.hpp"
#include "vector.hpp"
#include "acquarioview.hpp"
// controller

Controller::Controller(QObject* parent) : QObject(parent), _timer(new QTimer()), _model(nullptr), _view(nullptr) {
    connect(_timer, SIGNAL(timeout()), this, SLOT(advance()));
    // connect(_timer, SIGNAL(timeout()), _scene, SLOT(QGraphicsScene::advance())); // non alla scene maaa...
}

Controller::~Controller() {
    // fishControllers are handled by default by the deepptr in the vecotr
    //  vegControllers are handled by default by the deepptr in the vector
    delete _timer;
}

void Controller::setModel(Aquarius* model) {
    _model = model;
}

void Controller::setView(AcquarioView* view) {
    _view = view;
    // connect(_timer, SIGNAL(timeout()), _view, SLOT(update()));
}

const Vector<DeepPtr<Fish>> &Controller::getAllFish()
{
    return _model->getAllFish();
}

const Vector<DeepPtr<Vegetale>>& Controller::getAllVegetale(){
    return _model->getAllVegetale();
}

void Controller::addPredatore(const Vect2D& position) {
    _model->addFish(new Predatore(position, "paolo"));
}

void Controller::addVegetale(const Vect2D & position){
    _model->addVegetale(new Vegetale(position));
}

void Controller::resize(int width, int height) {
    _model->setSize(width, height);
}

void Controller::remFish() {}
void Controller::remVegetale() {}
// #include <iostream>
void Controller::advance() {
    // std::cout << "advance"<< std::endl;
    _model->advance();
}

void Controller::start() {
    _timer->start(20);
}
void Controller::stop() {
    _timer->stop();
}

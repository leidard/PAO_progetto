#include "controller.hpp"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QPointF>
#include <QTimer>

#include "aquarius.hpp"
#include "deepptr.hpp"
#include "fish.hpp"
#include "middlewares/fishcreator.hpp"
#include "middlewares/foodcreator.hpp"
#include "preda.hpp"
#include "predatore.hpp"
#include "vect2d.hpp"
#include "vector.hpp"
#include "view.hpp"

// fish controller

Controller::FishController::FishController() : _fishmodel(nullptr), _fishview(nullptr) {}

void Controller::FishController::setModel(Fish* model) {
    _fishmodel = model;
}
void Controller::FishController::setView(FishView* view) {
    _fishview = view;
    QPixmap p = QPixmap(_fishmodel->getImagePath().c_str()).scaled(QSize(20, 20));

    p.fill(Qt::GlobalColor::red);

    _fishview->setPixmap(p);
}

FishView* Controller::FishController::view() {
    return _fishview;
}

QPointF Controller::FishController::getPosition() const {
    Vect2D a = _fishmodel->getPosition();
    return QPointF(a.x(), a.y());
}
double Controller::FishController::getRotation() const {
    return _fishmodel->getVelocity().angleDeg();
}

// vegetale controller

Controller::VegetaleController::VegetaleController(Vegetale*, QGraphicsScene*) {}

void Controller::VegetaleController::setModel(Vegetale* model) { _vegmodel = model; }
void Controller::VegetaleController::setView(VegetaleView* view) { _vegview = view; }

VegetaleView* Controller::VegetaleController::view() {
    return _vegview;
}

QPointF Controller::VegetaleController::getPosition() const {}

// controller

Controller::Controller(QObject* parent) : QObject(parent), _timer(new QTimer()), _model(Aquarius::getInstance()), _view(nullptr), _scene(new QGraphicsScene(this)) {
    connect(_timer, SIGNAL(timeout()), this, SLOT(advance()));
    connect(_timer, SIGNAL(timeout()), _scene, SLOT(QGraphicsScene::advance()));
}

Controller::~Controller() {
    // fishControllers are handled by default by the deepptr in the vecotr
    //  vegControllers are handled by default by the deepptr in the vector
    delete _timer;
}

void Controller::setModel(Aquarius* model) {
    _model = model;
}

void Controller::setView(QGraphicsView* view) {
    _view = view;
    _view->setScene(_scene);
    _view->setRenderHint(QPainter::Antialiasing);
}

void Controller::addPredatore() {
    auto model = FishCreator().createPredatore(Vect2D(100, 100));
    auto view = new FishView();
    auto controller = new FishController();
    controller->setModel(model);
    controller->setView(view);
    view->setController(controller);

    fishControllers.push_back(controller);
}

void Controller::addVegetale(Vegetale*) {
}

void Controller::remFish() {}
void Controller::remVegetale() {}

void Controller::advance() {
    _model->advance();
    _scene->update();
}

void Controller::start() {
    _timer->start(40);
}
void Controller::stop() {
    _timer->stop();
}
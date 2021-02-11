#include "infocontroller.hpp"
#include "infoview.hpp"

#include <QTimer>
#include <QString>

InfoController::InfoController(): QObject(), _model(nullptr), _view(nullptr), _timer(new QTimer()), pos(0)  {
    connect(_timer, &QTimer::timeout, this, &InfoController::tick);
}

InfoController::~InfoController() {
    delete _timer;
}

// publics

void InfoController::setModel(Aquarius* model) {
    _model = model;
}

void InfoController::setView(InfoView* view) {
    _view = view;
}

bool InfoController::isVisible() const {
    return _view->isVisible();
}

unsigned int InfoController::getSize()const {
    return _model->getAllOrganismi().size();
}

unsigned int InfoController::getPosition()const {
    return pos;
}

Organismo* InfoController::getCurrent() const {
    if (getSize() > 0 && pos < getSize()) {
            return _model->getAllOrganismi()[pos].get();
        } else 
            return nullptr;
}

bool InfoController::hasNext() const {
    return pos < _model->getAllOrganismi().size() - 1;
}

bool InfoController::hasPrev() const  {
    return pos > 0;
}

// slots

void InfoController::show() {
    _view->show();
    _timer->start(20);
}

void InfoController::close() {
    _timer->stop();
    _view->close();
    std::cout << "closed" << std::endl;
} 

void InfoController::tick() {
    if (_view->isVisible()) {
        if (getSize() > 0) {
            if (pos >= getSize()) pos = getSize() - 1;
            _view->setData(_model->getAllOrganismi()[pos].get());
        } else 
            _view->setData();
    } else {
        _timer->stop();
    }
}

void InfoController::next() {
    if (hasNext())
        pos++;
}

void InfoController::prev() {
    if (hasPrev())
        pos--;
}

void InfoController::updateNameOfCurrent(const QString& name) {
    if (pos < _model->getAllOrganismi().size())
        _model->getAllOrganismi()[pos]->setName(name.toStdString());
}

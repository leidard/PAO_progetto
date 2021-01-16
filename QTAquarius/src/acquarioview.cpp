#include "acquarioview.hpp"

#include <QMenuBar>
#include <QPaintEvent>
#include <QPainter>
#include <QVBoxLayout>

#include "organismoinfoview.hpp"
#include "sardina.hpp"
#include "tonno.hpp"

const Vect2D AcquarioView::shape[3] = {
    Vect2D(20.0, 0.0),
    Vect2D(-9.0, -10.0),
    Vect2D(-9.0, 10.0)};

const unsigned int AcquarioView::minColor = 0xff00;
const unsigned int AcquarioView::maxColor = 0xff0000;
const double AcquarioView::minScale = .8;
const double AcquarioView::maxScale = 1;

AcquarioView::AcquarioView(QWidget* parent) : QWidget(parent), drawing(Tool::NIENTE), pausa(false), minVal(10000), maxVal(0) {
    layout = new QVBoxLayout(this);
    menuBar = new QMenuBar(this);
    // TO DO: Creare un .qss per lo stylesheet!
    setStyleSheet("background-color: #70dbe9;");
    menuBar->setStyleSheet(QString("background-color: white; QMenu::item:selected { color: black}, QMenu::item::hover { color: black}"));

    file = new QMenu("File", menuBar);
    strumenti = new QMenu("Aggiungi Organismo", menuBar);

    //FILE
    fileSalva = new QAction("Salva", this);
    fileCarica = new QAction("Carica", this);

    file->addAction(fileSalva);
    file->addAction(fileCarica);

    //STRUMENTI
    strumentiOptions = new QActionGroup(this);
    aggiungiSardina = new QAction("Aggiungi sardina", this);
    aggiungiSardina->setCheckable(true);
    connect(aggiungiSardina, &QAction::triggered, this, &AcquarioView::drawSardina);
    aggiungiTonno = new QAction("Aggiungi tonno", this);
    aggiungiTonno->setCheckable(true);
    connect(aggiungiTonno, &QAction::triggered, this, &AcquarioView::drawTonno);

    strumentiOptions->addAction(aggiungiSardina);
    strumentiOptions->addAction(aggiungiTonno);

    connect(strumentiOptions, &QActionGroup::triggered, [](QAction* action) {
        static QAction* lastAction = nullptr;
        if (action == lastAction) {  // entro qua se lastAction == nullptr == action ??
            // se dovessi entrare qua sarebbe un Undefined Behaviour!!!!!
            action->setChecked(false);
            lastAction = nullptr;
        } else
            lastAction = action;
    });

    infoPesci = new QAction("Info organismi", this);
    connect(infoPesci, &QAction::triggered, this, &AcquarioView::openInfo);

    strumenti->addAction(aggiungiSardina);
    strumenti->addAction(aggiungiTonno);
    strumenti->addAction(infoPesci);

    //PAUSA E RIPRENDI
    pausariprendi = new QAction("Pausa", menuBar);
    connect(pausariprendi, &QAction::triggered, this, &AcquarioView::stopGo);

    menuBar->addMenu(file);
    menuBar->addMenu(strumenti);
    menuBar->addAction(pausariprendi);
    //    menuBar->addAction("Riprendi");
    layout->setMenuBar(menuBar);

    infoView = new OrganismoInfoView(this);

    resize(QSize(1024, 720));  //starting window size
}

void AcquarioView::openInfo() {
    infoView->show();
    // connect(this, &AcquarioView::update, infoView, &FishInfoView::updateInfo);
}

void AcquarioView::drawSardina() {
    if (drawing == Tool::SARDINA)
        drawing = Tool::NIENTE;
    else
        drawing = Tool::SARDINA;
}

void AcquarioView::drawTonno() {
    if (drawing == Tool::TONNO)
        drawing = Tool::NIENTE;
    else
        drawing = Tool::TONNO;
}

void AcquarioView::stopGo() {
    if (!pausa) {
        controller->stop();
        pausariprendi->setText("Pausa");
        pausa = true;
    } else {
        controller->start();
        pausariprendi->setText("Riprendi");
        pausa = false;
    }
}

void AcquarioView::setController(Controller* c) {
    controller = c;
    infoView->setController(controller);
}

void AcquarioView::resizeEvent(QResizeEvent* event) {
    QSize s = event->size();
    controller->resize(s.width(), s.height());
}

void AcquarioView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && drawing == Tool::TONNO) {
        controller->addTonno(Vect2D(event->x(), event->y()));
    } else if (event->button() == Qt::LeftButton && drawing == Tool::SARDINA) {
        controller->addSardina(Vect2D(event->x(), event->y()));
    }
}

#include <iostream>

void AcquarioView::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);

    for (auto& o : controller->getAllOrganismi()) {
        unsigned int val = o->getValoreNutrizionale();
        if (val > maxVal) maxVal = val;
        if (val < minVal) minVal = val;
        double p = 1.0;
        unsigned int color = 0x0;
        if (minVal < maxVal) {
            p = (val - minVal) / (double)(maxVal - minVal);
            color = minColor + p * (maxColor - minColor);
        }

        const Vect2D& pos = o->getPosition();
        double angle = o->getVelocity().angleRad();
        double scale = minScale + p * (maxScale - minScale);
        Vect2D s[3];
        s[0] = shape[0].rotateRad(angle).mult(scale).add(pos);
        s[1] = shape[1].rotateRad(angle).mult(scale).add(pos);
        s[2] = shape[2].rotateRad(angle).mult(scale).add(pos);
        QPointF points[3] = {
            QPointF(s[0].x(), s[0].y()),
            QPointF(s[1].x(), s[1].y()),
            QPointF(s[2].x(), s[2].y())};
        painter.setBrush(QBrush(QColor(QRgb(color))));
        painter.drawPolygon(points, 3);
    }
}

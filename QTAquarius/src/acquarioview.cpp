#include "acquarioview.hpp"

#include <QMenuBar>
#include <QPaintEvent>
#include <QPainter>
#include <QVBoxLayout>

#include "organismoinfoview.hpp"
#include "sardina.hpp"
#include "tonno.hpp"

const Vect2D AcquarioView::vertex[3] = {
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
    menuBar->setStyleSheet(QString("color:black; background-color: white; QMenu::item:selected { color: black}, QMenu::item::hover { color: black}"));

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

bool AcquarioView::isInfoViewVisible() const { return infoView->isVisible(); }

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

void AcquarioView::shader(const Vect2D* v, unsigned int s, const Vect2D& position, double angle, QPointF* dest, double scale) {
    for (unsigned int i = 0; i < s; ++i) {
        std::pair<double, double> p = v[i].rotateRad(angle).mult(scale).add(position).getPair();
        dest[i] = QPointF(p.first, p.second);
    }
}

#include <QPen>

void AcquarioView::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    for (auto& o : controller->getAllOrganismi()) {
        unsigned int val = o->getValoreNutrizionale();
        if (val > maxVal) maxVal = val;
        if (val < minVal) minVal = val;
        double p = 1.0;
        unsigned int color = minColor;
        if (minVal < maxVal) {
            p = (val - minVal) / (double)(maxVal - minVal);
            color = minColor + p * (maxColor - minColor);
        }

        QPointF points[3];

        double scale = minScale + p * (maxScale - minScale);
        shader(vertex, 3, o->getPosition(), o->getVelocity().angleRad(), points, scale);

        if (infoView->isVisible() && &(*o) == controller->getCurrent()) {
            painter.save();
            Vect2D center = o->getPosition();
            painter.setBrush(Qt::NoBrush);
            painter.drawEllipse(QPointF(center.x(), center.y()), 100, 100);
            painter.restore();
        }

        painter.setBrush(QColor(QRgb(color)));
        painter.drawPolygon(points, 3);
    }
}

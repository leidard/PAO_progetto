#include "acquarioview.hpp"

#include <QMenuBar>
#include <QPaintEvent>
#include <QPainter>
#include <QVBoxLayout>

#include "organismoinfoview.hpp"
#include "sardina.hpp"
#include "tonno.hpp"

AcquarioView::AcquarioView(QWidget* parent) : QWidget(parent), drawing(Tool::NIENTE), pausa(false) {
    layout = new QVBoxLayout(this);
    menuBar = new QMenuBar(this);
    // TO DO: Creare un .qss per lo stylesheet!
    setStyleSheet("background-color: #70dbe9;");
    menuBar->setStyleSheet(QString("background-color: white; QMenu::item:selected { color: black}, QMenu::item::hover { color: black}"));

    file = new QMenu("File", menuBar);
    strumenti = new QMenu("Strumenti", menuBar);

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

void AcquarioView::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    int i = 0;
    auto& organismi = controller->getAllOrganismi();
    for (auto& o : organismi) {
        Vect2D pos = o->getPosition();
        Vect2D vel = o->getVelocity();
        Vect2D left = Vect2D::rotateDeg(vel, -145);
        Vect2D right = Vect2D::rotateDeg(vel, 145);
        if (o->getType() == "tonno") {
            vel.setMagnitude(15);
            left.setMagnitude(20);
            right.setMagnitude(20);
        } else if (o->getType() == "sardina"){
            vel.setMagnitude(10);
            left.setMagnitude(15);
            right.setMagnitude(15);
        }
        Vect2D fut = pos + vel;
        Vect2D futl = pos + left;
        Vect2D futr = pos + right;
        // painter.drawRect(pos.x()-10, pos.y()-10, 20, 20);
        // painter.drawLine(pos.x(), pos.y(), fut.x(), fut.y());
        // painter.drawLine(futl.x(), futl.y(), pos.x(), pos.y());
        // painter.drawLine(futr.x(), futr.y(), pos.x(), pos.y());
        // painter.drawLine(futr.x(), futr.y(), fut.x(), fut.y());
        QPointF points[3] = {
            QPointF(futl.x(), futl.y()),
            QPointF(futr.x(), futr.y()),
            QPointF(fut.x(), fut.y())};
        painter.setBrush(QBrush(QColor(o->getType() == "tonno" ? "red" : "green")));
        //        QPixmap pix = QPixmap(":/images/punto.png");
        //        painter.drawPixmap(points, pix);
        painter.drawPolygon(points, 3);
        i++;
    }
}

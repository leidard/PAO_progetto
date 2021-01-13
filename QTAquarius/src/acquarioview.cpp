#include "acquarioview.hpp"

#include <QMenuBar>
#include <QPaintEvent>
#include <QPainter>
#include <QVBoxLayout>

#include "fishinfoview.hpp"
#include "pescevolante.hpp"
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
    aggiungiPesceVolante = new QAction("Aggiungi pesce volante", this);
    aggiungiPesceVolante->setCheckable(true);
    connect(aggiungiPesceVolante, &QAction::triggered, this, &AcquarioView::drawPesceVolante);
    aggiungiTonno = new QAction("Aggiungi tonno", this);
    aggiungiTonno->setCheckable(true);
    connect(aggiungiTonno, &QAction::triggered, this, &AcquarioView::drawTonno);

    strumentiOptions->addAction(aggiungiPesceVolante);
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

    infoPesci = new QAction("Info pesci", this);
    connect(infoPesci, &QAction::triggered, this, &AcquarioView::openInfo);

    strumenti->addAction(aggiungiPesceVolante);
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

    infoView = new FishInfoView(this);

    resize(QSize(1024, 720));  //starting window size
}

void AcquarioView::openInfo() {
    infoView->show();
    // connect(this, &AcquarioView::update, infoView, &FishInfoView::updateInfo);
}

void AcquarioView::drawPesceVolante() {
    if (drawing == Tool::PESCEVOLANTE)
        drawing = Tool::NIENTE;
    else
        drawing = Tool::PESCEVOLANTE;
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
    } else if (event->button() == Qt::LeftButton && drawing == Tool::PESCEVOLANTE) {
        controller->addPesceVolante(Vect2D(event->x(), event->y()));
    }
}

void AcquarioView::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    int i = 0;
    auto& fish = controller->getAllFish();
    for (auto& f : fish) {
        Vect2D pos = f->getPosition();
        Vect2D vel = f->getVelocity();
        Vect2D left = Vect2D::rotateDeg(vel, -145);
        Vect2D right = Vect2D::rotateDeg(vel, 145);
        if (f->getType() == "tonno") {
            vel.setMagnitude(15);
            left.setMagnitude(20);
            right.setMagnitude(20);
        } else {
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
        painter.setBrush(QBrush(QColor(f->getType() == "tonno" ? "red" : "green")));
        //        QPixmap pix = QPixmap(":/images/punto.png");
        //        painter.drawPixmap(points, pix);
        painter.drawPolygon(points, 3);
        i++;
    }
}

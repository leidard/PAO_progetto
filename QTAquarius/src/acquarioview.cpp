#include "acquarioview.hpp"

#include "deepptr.hpp"
#include "fish.hpp"
#include "fishinfoview.hpp"
#include "preda.hpp"
#include "predatore.hpp"
#include "vect2d.hpp"

AcquarioView::AcquarioView(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* main = new QVBoxLayout(this);
    QMenuBar* menuBar = new QMenuBar(this);
    QString styleBar = "QMenu::item:selected { color: black;}";
    menuBar->setStyleSheet(styleBar);

    QMenu* file = new QMenu("File", menuBar);
    QMenu* strumenti = new QMenu("Strumenti", menuBar);

    //FILE
    QAction* fileSalva = new QAction("Salva", this);
    QAction* fileCarica = new QAction("Carica", this);

    file->addAction(fileSalva);
    file->addAction(fileCarica);

    //STRUMENTI
    QActionGroup* strumentiOptions = new QActionGroup(this);
    QAction* aggiungiPreda = new QAction("Aggiungi preda", this);
    aggiungiPreda->setCheckable(true);
    //  connect(aggiungiPreda, SIGNAL(triggered()), this, SLOT());
    QAction* aggiungiPredatore = new QAction("Aggiungi predatore", this);
    aggiungiPredatore->setCheckable(true);

    strumentiOptions->addAction(aggiungiPreda);
    strumentiOptions->addAction(aggiungiPredatore);

    QAction* infoPesci = new QAction("Info pesci", this);
    connect(infoPesci, SIGNAL(triggered()), this, SLOT(openInfo()));

    strumenti->addAction(aggiungiPreda);
    strumenti->addAction(aggiungiPredatore);
    strumenti->addAction(infoPesci);

    menuBar->addMenu(file);
    menuBar->addMenu(strumenti);
    //menuBar->setStyleSheet("background-color: white");
    main->setMenuBar(menuBar);

    resize(QSize(1024, 720));  //starting window size
}

void AcquarioView::openInfo() {
    infoView = new FishInfoView(controller, this);
}

void AcquarioView::setController(Controller* c) {
    controller = c;
}

void AcquarioView::resizeEvent(QResizeEvent* event) {
    QSize s = event->size();
    controller->resize(s.width(), s.height());
}


void AcquarioView::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int i = 0;
    auto& fish = controller->getAllFish();
    for (auto& f : fish) {
        Vect2D pos = f->getPosition();
        Vect2D vel = f->getVelocity().setMagnitude(15);
        Vect2D left = Vect2D::rotate(vel, -2.5).setMagnitude(20);
        Vect2D right = Vect2D::rotate(vel, 2.5).setMagnitude(20);
        Vect2D fut = pos + vel;
        Vect2D futl = pos + left;
        Vect2D futr = pos + right;
        // painter.drawRect(pos.x()-10, pos.y()-10, 20, 20);
        // painter.drawLine(pos.x(), pos.y(), fut.x(), fut.y());
        // painter.drawLine(futl.x(), futl.y(), pos.x(), pos.y());
        // painter.drawLine(futr.x(), futr.y(), pos.x(), pos.y());
        // painter.drawLine(futr.x(), futr.y(), fut.x(), fut.y());
        QPointF* points = new QPointF[3];
        points[0] = QPointF(futl.x(), futl.y());
        points[1] = QPointF(futr.x(), futr.y());
        points[2] = QPointF(fut.x(), fut.y());

        painter.setBrush(QBrush(QColor(f->getType() == "predatore" ? "red" : "green")));
        //        QPixmap pix = QPixmap(":/images/punto.png");
        //        painter.drawPixmap(points, pix);
        painter.drawPolygon(points, 3);
        //connect(pix, SIGNAL(triggered()), this, SLOT(openInfo(i)));
        i++;
    }

    //    auto veggies = controller->getAllFish();
    //    for (auto &f : veggies) {
    //        Vect2D pos = f->getPosition();
    //        QPointF* points = new QPointF[3];
    //        points[0] = QPointF(100, 100);
    //        points[1] = QPointF(110, 110);
    //        points[2] = QPointF(90, 90);
    //        painter.setBrush(QBrush(QColor("black")));
    //        painter.drawPolygon(points, 3);
}

//void AcquarioView::timerEvent(QTimerEvent* event) {
//    auto fishes = controller->getAllFish();
//    double val = fishes[0]->getStamina().getVal();
//    bar->setValue(val);
//}

//controller->getFish();
//controller->getVegetali();
//}

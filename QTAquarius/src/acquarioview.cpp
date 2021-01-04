#include "acquarioview.hpp"

#include "deepptr.hpp"
#include "fish.hpp"
#include "fishinfoview.hpp"
#include "preda.hpp"
#include "predatore.hpp"
#include "vect2d.hpp"

AcquarioView::AcquarioView(QWidget* parent) : QWidget(parent), drawingPreda(false), drawingPredatore(false) {
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
    aggiungiPreda = new QAction("Aggiungi preda", this);
    aggiungiPreda->setCheckable(true);
    connect(aggiungiPreda, &QAction::triggered, this, &AcquarioView::drawPreda);
    aggiungiPredatore = new QAction("Aggiungi predatore", this);
    aggiungiPredatore->setCheckable(true);
    connect(aggiungiPredatore, &QAction::triggered, this, &AcquarioView::drawPredatore);


    strumentiOptions->addAction(aggiungiPreda);
    strumentiOptions->addAction(aggiungiPredatore);

    connect(strumentiOptions, &QActionGroup::triggered, [](QAction* action) {
        static QAction* lastAction = nullptr;
        if (action == lastAction)
        {
          action->setChecked(false);
          lastAction = nullptr;
        }
        else
          lastAction = action;
      });

    infoPesci = new QAction("Info pesci", this);
    connect(infoPesci, &QAction::triggered, this, &AcquarioView::openInfo);

    strumenti->addAction(aggiungiPreda);
    strumenti->addAction(aggiungiPredatore);
    strumenti->addAction(infoPesci);

    menuBar->addMenu(file);
    menuBar->addMenu(strumenti);
    layout->setMenuBar(menuBar);

    resize(QSize(1024, 720));  //starting window size
}

void AcquarioView::openInfo() {
    infoView = new FishInfoView(controller, this);
}

void AcquarioView::drawPreda(){
    drawingPreda = drawingPreda ? false : true;
    drawingPredatore = false;
}

void AcquarioView::drawPredatore(){
    drawingPredatore = drawingPredatore ? false : true;
    drawingPreda = false;
}

void AcquarioView::setController(Controller* c) {
    controller = c;
}

void AcquarioView::resizeEvent(QResizeEvent* event) {
    QSize s = event->size();
    controller->resize(s.width(), s.height());
}

void AcquarioView::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && drawingPredatore) {
        controller->addPredatore(Vect2D(event->x(), event->y()));
    }else if(event->button() == Qt::LeftButton && drawingPreda) {
        controller->addPreda(Vect2D(event->x(), event->y()));
    }
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

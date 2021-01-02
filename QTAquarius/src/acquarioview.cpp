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
    std::cout << "BELLAAAAA";
    //    infoView = new FishInfoView(this);
    //    infoView->show();

    timerID = startTimer(100);
    int i = 0;  //i è da passare come param ed è il numero del pesce nell'array pesci
    dialog = new QDialog();
    dialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);  //disable "?" button
    dialog->setMinimumSize(QSize(300, 180));
    dialog->setMaximumSize(QSize(300, 180));

    QGridLayout* grid = new QGridLayout(dialog);

    auto& fishes = controller->getAllFish();
    //ICON
    if (fishes[i]->getType() == "predatore") {  //draw icon for Predatore
        QLabel* img = new QLabel(dialog);
        QPixmap pix = QPixmap(":/images/punto.png");
        pix = pix.scaled(img->size(), Qt::KeepAspectRatio);
        img->setPixmap(pix);
        grid->addWidget(img, 0, 0, 1, 1);
    } else if (fishes[i]->getType() == "preda") {  //draw icon for Preda
        //Immagine pesce
        QLabel* img = new QLabel(dialog);
        QPixmap pix = QPixmap(":/images/punto.png");
        pix = pix.scaled(img->size(), Qt::KeepAspectRatio);
        img->setPixmap(pix);
        grid->addWidget(img, 0, 0, 1, 1);
    }

    //NAME
    QString name((fishes[i]->getName()).c_str());
    nameLine = new QLineEdit(dialog);
    nameLine->setMaxLength(30);
    nameLine->setText(name);
    grid->addWidget(new QLabel("Nome:"), 0, 1, 1, 1);
    grid->addWidget(nameLine, 0, 2, 1, 1);
    connect(nameLine, SIGNAL(textEdited(QString)), this, SLOT(saveInfo()));

    //TYPE
    QString type((fishes[i]->getType()).c_str());
    grid->addWidget(new QLabel("Tipologia:"), 1, 0, 1, 1);
    grid->addWidget(new QLabel(type), 1, 1, 1, 1);

    //NUTRITIONAL VALUE
    QString nutVal = QString::number(fishes[i]->getValoreNutrizionale());
    grid->addWidget(new QLabel("Valore nutrizionale:"), 2, 0, 1, 1);
    grid->addWidget(new QLabel(nutVal), 2, 1, 1, 1);

    //STATUS
    status = new QLabel("alive");
    grid->addWidget(new QLabel("Status: "), 3, 0, 1, 1);
    grid->addWidget(status, 3, 1, 1, 1);

    //STAMINA BAR
    bar = new QProgressBar(dialog);
    bar->setMaximum(10);
    double val = fishes[0]->getStamina().getVal();
    bar->setValue(val);
    connect(bar, SIGNAL(valueChanged(int)), this, SLOT(dead()));
    grid->addWidget(new QLabel("Stamina:"), 4, 0, 1, 1);
    grid->addWidget(bar, 4, 1, 1, 2);

    //    //SAVE BUTTON (?)
    //    QPushButton* saveButton = new QPushButton("Salva", dialog);
    //    grid->addWidget(saveButton, 4, 0, 1, 1);
    //    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveInfo(i)));

    //QUIT BUTTON
    QPushButton* quitButton = new QPushButton("Annulla", dialog);
    connect(quitButton, SIGNAL(released()), this, SLOT(close()));
    grid->addWidget(quitButton, 5, 2, 1, 1);

    dialog->setLayout(grid);
    dialog->resize(400, 400);
    dialog->exec();
}

void AcquarioView::saveInfo() {
    std::cout << "SAVE";
    auto& fishes = controller->getAllFish();
    fishes[0]->setName(nameLine->text().toStdString());
    std::cout << nameLine->text().toStdString();
}

void AcquarioView::dead() {
    if (bar->value() == 0) status->setText("morto");
}

void AcquarioView::close() {
    dialog->close();
}

void AcquarioView::setController(Controller* c) {
    controller = c;
}

void AcquarioView::resizeEvent(QResizeEvent* event) {
    QSize s = event->size();
    controller->resize(s.width(), s.height());
}

#include <QBrush>
#include <QColor>
#include <QPointF>
#include <iostream>
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
        painter.setBrush(QBrush(QColor("red")));
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

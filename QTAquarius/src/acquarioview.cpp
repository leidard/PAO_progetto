#include <QCloseEvent>
#include <QMessageBox>
#include <QMenuBar>
#include <QPaintEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QPen>
#include <QFileDialog>
#include <QInputDialog>

#include "acquarioview.hpp"


const Vect2D AcquarioView::vertex[3] = {
    Vect2D(20.0, 0.0),
    Vect2D(-9.0, -10.0),
    Vect2D(-9.0, 10.0)};

const unsigned int AcquarioView::minColor = 0x00ff00;
const unsigned int AcquarioView::maxColor = 0xff0000;
const double AcquarioView::minScale = .6;
const double AcquarioView::maxScale = 1;

AcquarioView::AcquarioView(QWidget* parent) : QWidget(parent), pausa(false), minVal(10000), maxVal(0) {
    QFile styleSheetFile(":/style/stylesheet.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    setStyleSheet(styleSheet);
    setObjectName("main");

    layout = new QVBoxLayout(this);
    menuBar = new QMenuBar(this);
    file = new QMenu("File", menuBar);
    aggOrg = new QMenu("Aggiungi organismi", menuBar);
    simulazione = new QMenu("Simulazione", menuBar);

    // FILE
    fileSalva = new QAction("Salva", this);
    connect(fileSalva, &QAction::triggered, this, &AcquarioView::save);
    fileCarica = new QAction("Carica", this);
    connect(fileCarica, &QAction::triggered, this, &AcquarioView::load);
    fileRinomina = new QAction("Rinomina acquario", this);
    connect(fileRinomina, &QAction::triggered, this, &AcquarioView::rename);

    file->addAction(fileSalva);
    file->addAction(fileCarica);
    file->addAction(fileRinomina);

    // AGGIUNGI ORGANISMO
    strumentiOptions = new QActionGroup(this);
    aggiungiSardina = new QAction("Aggiungi sardina", strumentiOptions);
    aggiungiSardina->setCheckable(true);
    aggiungiTonno = new QAction("Aggiungi tonno", strumentiOptions);
    aggiungiTonno->setCheckable(true);
    aggiungiPhytoplankton = new QAction("Aggiungi phytoplankton", strumentiOptions);
    aggiungiPhytoplankton->setCheckable(true);

    strumentiOptions->addAction(aggiungiSardina);
    strumentiOptions->addAction(aggiungiTonno);
    strumentiOptions->addAction(aggiungiPhytoplankton);

    connect(strumentiOptions, &QActionGroup::triggered, [](QAction* action) {
        static QAction* lastAction = nullptr;
        if (action && action == lastAction) {
            action->setChecked(false);
            lastAction = nullptr;
        } else
            lastAction = action;
    });

    aggOrg->addAction(aggiungiSardina);
    aggOrg->addAction(aggiungiTonno);
    aggOrg->addAction(aggiungiPhytoplankton);

    // INFO ORGANISMI
    infoPesci = new QAction("Info organismi", menuBar);

    // SIMULAZIONE
    pausariprendi = new QAction("Pausa/Riprendi", simulazione);

    autorespawn = new QAction("Respawn automatico", simulazione);
    autorespawn->setCheckable(true);
    autorespawn->setChecked(false);
    
    
    simulazione->addAction(pausariprendi);
    simulazione->addAction(autorespawn);

    // MENUBAR
    menuBar->addMenu(file);
    menuBar->addMenu(aggOrg);
    menuBar->addAction(infoPesci);
    menuBar->addMenu(simulazione);

    layout->setMenuBar(menuBar);

    resize(QSize(1024, 720));  //starting window size
    setMinimumWidth(1024);
    setMinimumHeight(720);
}

void AcquarioView::stopGo() {
    if (controller->isRunning()) {
        controller->stop();
        pausariprendi->setText("Riprendi");
    } else {
        controller->start();
        pausariprendi->setText("Pausa");
    }
}

void AcquarioView::save(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Salva file"), QDir::currentPath(), tr("JSON (*.json)"));
    controller->saveData(fileName.toStdString(), windowTitle().toStdString());

}

void AcquarioView::load(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Carica file"), QDir::currentPath(), tr("JSON (*.json)"));
    controller->loadData(fileName.toStdString());
    setWindowTitle(controller->getAquariusName().c_str());
}

void AcquarioView::rename(){
    bool ok;
    QString text = QInputDialog::getText(this, tr("Rinomina"), tr("Rinomina l'acquario:"), QLineEdit::Normal, windowTitle(), &ok);
   if (ok && !text.isEmpty()) setWindowTitle(text);
}

void AcquarioView::setController(Controller* c) {
    controller = c;
    setWindowTitle(controller->getAquariusName().c_str());

    connect(infoPesci, &QAction::triggered, controller, &Controller::openInfo);
    connect(autorespawn, &QAction::triggered, controller, &Controller::toggleAutoRespawn);
    connect(pausariprendi, &QAction::triggered, controller, &Controller::toggleRunning);
    connect(aggiungiSardina, &QAction::triggered, controller, &Controller::drawSardina);
    connect(aggiungiTonno, &QAction::triggered, controller, &Controller::drawTonno);
    connect(aggiungiPhytoplankton, &QAction::triggered, controller, &Controller::drawPhytoplankton);
}

void AcquarioView::resizeEvent(QResizeEvent* event) {
    QSize s = event->size();
    controller->resize(s.width(), s.height());
}

void AcquarioView::shader(const Vect2D* v, unsigned int s, const Vect2D& position, double angle, QPointF* dest, double scale) {
    for (unsigned int i = 0; i < s; ++i) {
        std::pair<double, double> p = v[i].rotateRad(angle).mult(scale).add(position).getPair();
        dest[i] = QPointF(p.first, p.second);
    }
}

unsigned int colorBetween(const unsigned int& first, const unsigned int& last, double scale) {
    unsigned int r1 = ((first >> 16) & 0xffu);
    unsigned int g1 = ((first >> 8) & 0xffu);
    unsigned int b1 = (first & 0xff);

    unsigned int r2 = ((last >> 16) & 0xffu);
    unsigned int g2 = ((last >> 8) & 0xffu);
    unsigned int b2 = (last & 0xff);

    unsigned int r = r1 + scale * (r2 - r1);
    unsigned int g = g1 + scale * (g2 - g1);
    unsigned int b = b1 + scale * (b2 - b1);

    return ((r & 0xffu) << 16) | ((g & 0xffu) << 8) | (b & 0xffu);
}

void AcquarioView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton){
       controller->useTool(Vect2D(event->x(), event->y()));
    }
}


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

            color = colorBetween(minColor, maxColor, p);
        }

        QPointF points[3];

        double scale = minScale + p * (maxScale - minScale);
        
        // std::cout << "scale: " << scale << ", color: " << std::hex << color << std::endl;
        shader(vertex, 3, o->getPosition(), o->getVelocity().angleRad(), points, scale);

        if (controller->isInfoViewVisible() && &(*o) == controller->getInfoCurrent()) {
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

void AcquarioView::closeEvent(QCloseEvent *event){
    if (QMessageBox::Yes == QMessageBox::question(this, "Conferma chiusura", "Le modifiche non salvate andranno perse, confermi di volere uscire?", QMessageBox::Yes | QMessageBox::No))
        event->accept();
    else
        event->ignore();
}


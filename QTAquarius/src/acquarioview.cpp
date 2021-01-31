#include "acquarioview.hpp"

const Vect2D AcquarioView::vertex[3] = {
    Vect2D(20.0, 0.0),
    Vect2D(-9.0, -10.0),
    Vect2D(-9.0, 10.0)};

const unsigned int AcquarioView::minColor = 0xff00;
const unsigned int AcquarioView::maxColor = 0xff0000;
const double AcquarioView::minScale = .8;
const double AcquarioView::maxScale = 1;

AcquarioView::AcquarioView(QWidget* parent) : QWidget(parent), drawing(Tool::NIENTE), pausa(false), saved(false), minVal(10000), maxVal(0) {
    QFile styleSheetFile(":/style/stylesheet.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    setStyleSheet(styleSheet);

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

    file->addAction(fileSalva);
    file->addAction(fileCarica);

    // AGGIUNGI ORGANISMO
    strumentiOptions = new QActionGroup(this);
    aggiungiSardina = new QAction("Aggiungi sardina", strumentiOptions);
    aggiungiSardina->setCheckable(true);
    connect(aggiungiSardina, &QAction::triggered, this, &AcquarioView::drawSardina);
    aggiungiTonno = new QAction("Aggiungi tonno", strumentiOptions);
    aggiungiTonno->setCheckable(true);
    connect(aggiungiTonno, &QAction::triggered, this, &AcquarioView::drawTonno);
    aggiungiPhytoplankton = new QAction("Aggiungi phytoplankton", strumentiOptions);
    aggiungiPhytoplankton->setCheckable(true);
    connect(aggiungiPhytoplankton, &QAction::triggered, this, &AcquarioView::drawPhytoplankton);

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
    connect(infoPesci, &QAction::triggered, this, &AcquarioView::openInfo);

    // SIMULAZIONE
    pausariprendi = new QAction("Pausa", simulazione);
    connect(pausariprendi, &QAction::triggered, this, &AcquarioView::stopGo);
    autorespawn = new QAction("Respawn automatico", simulazione);
    autorespawn->setCheckable(true);
    autorespawn->setChecked(false);
    connect(autorespawn, &QAction::triggered, this, &AcquarioView::toggleRespawn);
    
    simulazione->addAction(pausariprendi);
    simulazione->addAction(autorespawn);

    // MENUBAR

    menuBar->addMenu(file);
    menuBar->addMenu(aggOrg);
    menuBar->addAction(infoPesci);
    menuBar->addMenu(simulazione);

    layout->setMenuBar(menuBar);

    infoView = new OrganismoInfoView(this);

    resize(QSize(1024, 720));  //starting window size
    setMinimumWidth(1024);
    setMinimumHeight(720);
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

void AcquarioView::drawPhytoplankton(){
    if (drawing == Tool::PHYTOPLANKTON)
        drawing = Tool::NIENTE;
    else
        drawing = Tool::PHYTOPLANKTON;
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

void AcquarioView::toggleRespawn() {
    controller->toggleAutoRespawn();
    autorespawn->setChecked(controller->isAutoRespawnEnabled());
}

void AcquarioView::save(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), QDir::currentPath(), tr("JSON (*.json)"));
        //cambiare il path
    saved=true;
    //controller->saveData(fileName);
}

void AcquarioView::load(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load file"), QDir::currentPath(), tr("JSON (*.json)"));
    //cambiare il path
}

void AcquarioView::setController(Controller* c) {
    controller = c;
    infoView->setController(controller);
    setWindowTitle(controller->getAquariusName().c_str());
}

void AcquarioView::resizeEvent(QResizeEvent* event) {
    QSize s = event->size();
    controller->resize(s.width(), s.height());
}

void AcquarioView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && drawing == Tool::TONNO) {
        controller->addTonno(Vect2D(event->x(), event->y()));
    } if (event->button() == Qt::LeftButton && drawing == Tool::SARDINA) {
        controller->addSardina(Vect2D(event->x(), event->y()));
    } else if (event->button() == Qt::LeftButton && drawing == Tool::PHYTOPLANKTON) {
        controller->addPhytoplankton(Vect2D(event->x(), event->y()));
    }
}

void AcquarioView::shader(const Vect2D* v, unsigned int s, const Vect2D& position, double angle, QPointF* dest, double scale) {
    for (unsigned int i = 0; i < s; ++i) {
        std::pair<double, double> p = v[i].rotateRad(angle).mult(scale).add(position).getPair();
        dest[i] = QPointF(p.first, p.second);
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

void AcquarioView::closeEvent(QCloseEvent *event){
    if(!saved){
        event->ignore();
        if (QMessageBox::Yes == QMessageBox::question(this, "Conferma chiusura", "Sei sicuro di voler uscire senza salvare?", QMessageBox::Yes | QMessageBox::No))
            event->accept();
    }
}


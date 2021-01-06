#include "fishinfoview.hpp"

#include <sstream>

FishInfoView::FishInfoView(QWidget* parent) : QDialog(parent) {
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);  //disable "?" button
    setMinimumSize(QSize(350, 250));
    setMaximumSize(QSize(350, 250));
    QPoint dialogCenter = mapToGlobal(rect().center());
    QPoint parentWindowCenter = parent->window()->mapToGlobal(parent->window()->rect().center());
    move(parentWindowCenter - dialogCenter);  //mette la dialog al centro della main window

    layout = new QGridLayout(this);

    // IMAGE
    img = new QLabel(this);
    layout->addWidget(img, 0, 0, 1, 1);

    // NAME
    nameLine = new QLineEdit(this);
    nameLine->setMaxLength(30);
    connect(nameLine, &QLineEdit::textEdited, this, [this]() { controller->updateName(nameLine->text().toStdString()); });
    layout->addWidget(new QLabel("Nome:", this), 0, 1, 1, 1);
    layout->addWidget(nameLine, 0, 2, 1, 1);

    // TYPE
    tipologia = new QLabel("", this);
    layout->addWidget(new QLabel("Tipologia:", this), 1, 0, 1, 1);
    layout->addWidget(tipologia, 1, 1, 1, 1);

    // ValoreNutrizionale
    nutVal = new QLabel("", this);
    layout->addWidget(new QLabel("Valore nutrizionale:", this), 2, 0, 1, 1);
    layout->addWidget(nutVal, 2, 1, 1, 1);

    // STAMINA
    bar = new QProgressBar(this);
    bar->setMaximum(100);
    layout->addWidget(new QLabel("Stamina:", this), 4, 0, 1, 1);
    layout->addWidget(bar, 4, 1, 1, 2);

    // NEXT PREV
    previous = new QPushButton("Precedente", this);
    currentmax = new QLabel("0 di 0", this);
    next = new QPushButton("Successivo", this);
    connect(previous, &QPushButton::released, this, [this]() { controller->prev(); updateInfo(); });
    connect(next, &QPushButton::released, this, [this]() { controller->next(); updateInfo(); });
    layout->addWidget(previous, 5, 0, 1, 1);
    layout->addWidget(currentmax, 5, 1, 1, 1);
    layout->addWidget(next, 5, 2, 1, 1);

    quitButton = new QPushButton("Chiudi", this);
    connect(quitButton, &QPushButton::released, this, [this]() {killTimer(timerID); QDialog::close(); });
    layout->addWidget(quitButton, 6, 2, 1, 1);

    setLayout(layout);
}

void FishInfoView::closeEvent(QCloseEvent* event) {
    killTimer(timerID);
}

void FishInfoView::updateInfo() {
    const Fish* f = controller->getCurrent();
    if (f == nullptr) return;  // TODO call set default or something to reset all the values shown

    if (f->getType() == "predatore") {  //draw icon for Predatore
        QPixmap pix = QPixmap(":/images/punto.png");
        pix = pix.scaled(img->size(), Qt::KeepAspectRatio);
        img->setPixmap(pix);
    } else if (f->getType() == "preda") {  //draw icon for Preda
        QPixmap pix = QPixmap(":/images/punto.png");
        pix = pix.scaled(img->size(), Qt::KeepAspectRatio);
        img->setPixmap(pix);
    }

    nameLine->setText(f->getName().c_str());
    tipologia->setText(f->getType().c_str());
    nutVal->setNum(f->getValoreNutrizionale());
    bar->setValue(f->getStamina().getVal());
    std::stringstream s;
    s << controller->getPosition() << " di " << controller->getVectorSize();
    currentmax->setText(s.str().c_str());

    previous->setDisabled(!controller->hasPrev());
    next->setDisabled(!controller->hasNext());
}

void FishInfoView::show() {  //aggiungere i parent ovunque
    updateInfo();
    timerID = startTimer(100);
    QDialog::show();
}

void FishInfoView::setController(Controller* c) {
    controller = c;
}

void FishInfoView::timerEvent(QTimerEvent* event) {  //aggiorna la progress bar con la stamina
    std::cout << "updateInfo" << std::endl;
    updateInfo();
}

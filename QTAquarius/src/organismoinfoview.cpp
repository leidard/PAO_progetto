#include "organismoinfoview.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>
#include <sstream>

#include "organismo.hpp"

OrganismoInfoView::OrganismoInfoView(QWidget* parent) : QDialog(parent) {
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
    connect(quitButton, &QPushButton::released, this, [this]() { killTimer(timerID); QDialog::close(); });
    layout->addWidget(quitButton, 6, 2, 1, 1);

    setLayout(layout);
}

void OrganismoInfoView::closeEvent(QCloseEvent*) {
    killTimer(timerID);
}

void OrganismoInfoView::updateInfo() {
    const Organismo* o = controller->getCurrent();
    if (o == nullptr) return;  // TODO call set default or something to reset all the values shown
    if (!(controller->hasNext() || controller->hasPrev())) {
        controller->reset();
    }

    if (o->getType() == "tonno") {  //draw icon for Tonno
        QPixmap pix = QPixmap(":/images/punto.png");
        pix = pix.scaled(img->size(), Qt::KeepAspectRatio);
        img->setPixmap(pix);
    } else if (o->getType() == "sardina") {  //draw icon for Sardina
        QPixmap pix = QPixmap(":/images/punto.png");
        pix = pix.scaled(img->size(), Qt::KeepAspectRatio);
        img->setPixmap(pix);
    }

    nameLine->setText(o->getName().c_str());
    tipologia->setText(o->getType().c_str());
    nutVal->setNum(o->getValoreNutrizionale());
    bar->setValue(o->getStamina().getVal());
    std::stringstream s;
    s << (controller->getPosition() + 1) << " di " << controller->getVectorSize();
    currentmax->setText(s.str().c_str());

    previous->setDisabled(!controller->hasPrev());
    next->setDisabled(!controller->hasNext());
}

void OrganismoInfoView::show() {  //aggiungere i parent ovunque
    updateInfo();
    startTimer(100);
    QDialog::show();
}

void OrganismoInfoView::setController(Controller* c) {
    controller = c;
}

void OrganismoInfoView::timerEvent(QTimerEvent*) {  //aggiorna la progress bar con la stamina
    //std::cout << "updateInfo" << std::endl;
    updateInfo();
}

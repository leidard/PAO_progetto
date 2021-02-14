#include "infoview.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QFile>
#include <sstream>

#include "organismo.hpp"
#include "infocontroller.hpp"

InfoView::InfoView(QWidget* parent) : QDialog(parent) {
    setStyleSheet("QWidget { background-color: white; color: black; } MyDialog::title { height: 24px; font-weight: bold; color: #000000; background-color: #ffffff; } QProgressBar { text-align: center; border: 2px solid grey; border-radius: 5px; } QProgressBar::chunk { background-color: #66ff66; width: 5px; margin: 0.5px; } QPushButton{ border-style: solid; border-top-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgb(215, 215, 215), stop:1 rgb(222, 222, 222)); border-right-color: qlineargradient(spread:pad, x1:0, y1:0.5, x2:1, y2:0.5, stop:0 rgb(217, 217, 217), stop:1 rgb(227, 227, 227)); border-left-color: qlineargradient(spread:pad, x1:0, y1:0.5, x2:1, y2:0.5, stop:0 rgb(227, 227, 227), stop:1 rgb(217, 217, 217)); border-bottom-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgb(215, 215, 215), stop:1 rgb(222, 222, 222)); border-width: 1px; border-radius: 5px; color: rgb(0,0,0); padding: 2px; background-color: rgb(255,255,255); } QPushButton:hover{ border-style: solid; border-top-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgb(150, 150, 150), stop:1 rgb(150, 150, 150)); border-right-color: qlineargradient(spread:pad, x1:0, y1:0.5, x2:1, y2:0.5, stop:0 rgb(150, 150, 150), stop:1 rgb(150, 150, 150)); border-left-color: qlineargradient(spread:pad, x1:0, y1:0.5, x2:1, y2:0.5, stop:0 rgb(150, 150, 150), stop:1 rgb(150, 150, 150)); border-bottom-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgb(150, 150, 150), stop:1 rgb(150, 150, 150)); border-width: 1px; border-radius: 5px; color: rgb(0,0,0); padding: 2px; background-color: rgb(242, 242, 242); } QLineEdit { border: 2px solid gray; border-radius: 7px; padding: 0 8px; } QLineEdit:read-only { background: #f2f2f2; } QPushButton:disabled { background-color:#d5d5c3; }");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    move(parent->geometry().center());

    layout = new QGridLayout(this);

    // NAME
    nameLine = new QLineEdit(this);
    nameLine->setMaxLength(60);
    nameLine->setReadOnly(true);

    layout->addWidget(new QLabel("Nome:", this), 0, 0, 1, 1);
    layout->addWidget(nameLine, 0, 1, 1, 2);

    // TYPE
    tipologia = new QLabel("", this);
    layout->addWidget(new QLabel("Specie:", this), 1, 0, 1, 1);
    layout->addWidget(tipologia, 1, 1, 1, 1);

    // NUTRITIONAL VALUE
    nutVal = new QLabel("", this);
    layout->addWidget(new QLabel("Valore nutrizionale:", this), 2, 0, 1, 1);
    layout->addWidget(nutVal, 2, 1, 1, 1);

    // HUNGRY OR NOT
    hungry = new QLabel("", this);
    layout->addWidget(new QLabel("Affamato:", this), 3, 0, 1, 1);
    layout->addWidget(hungry, 3, 1, 1, 1);

    // STATUS
    status = new QLabel("", this);
    layout->addWidget(new QLabel("Stato:", this), 4, 0, 1, 1);
    layout->addWidget(status, 4, 1, 1, 1);

    // STAMINA
    staminaBar = new QProgressBar(this);
    staminaBar->setMaximum(100);
    layout->addWidget(new QLabel("Stamina:", this), 5, 0, 1, 1);
    layout->addWidget(staminaBar, 5, 1, 1, 2);

    // NEXT PREV
    previous = new QPushButton("Precedente", this);
    currentmax = new QLabel("0 di 0", this);
    next = new QPushButton("Successivo", this);

    layout->addWidget(previous, 6, 0, 1, 1);
    layout->addWidget(currentmax, 6, 1, 1, 1, Qt::AlignCenter);
    layout->addWidget(next, 6, 2, 1, 1);

    // QUIT
    quitButton = new QPushButton("Chiudi", this);
    layout->addWidget(quitButton, 7, 2, 1, 1);

    layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);
}


void InfoView::setData(Organismo* o) {
    if (o == nullptr) {
        setWindowTitle("Info organismo");
        nameLine->setText("");
        nameLine->setReadOnly(true);
        tipologia->setText("");
        nutVal->setNum(0);
        hungry->setText("");
        status->setText("");
        staminaBar->setValue(0);
        currentmax->setText("0 di 0");
        previous->setDisabled(true);
        next->setDisabled(true);
    }
    else {
        setWindowTitle(("Info oganismo: " + o->getName()).c_str());
        nameLine->setText(o->getName().c_str());
        nameLine->setReadOnly(false);
        tipologia->setText(QString::fromStdString(o->getSpecie()));
        nutVal->setNum(o->getValoreNutrizionale());
        if (o->isHungry())
            hungry->setText(QString("Sì"));
        else
            hungry->setText(QString("No"));
        if (o->isAwake())
            status->setText(QString("Sveglio"));
        else
            status->setText(QString("Addormentato"));

        staminaBar->setValue(o->getStamina() * 100);
        std::stringstream s;
        s << (controller->getPosition() + 1) << " di " << controller->getSize();
        currentmax->setText(s.str().c_str());

        previous->setDisabled(!controller->hasPrev());
        next->setDisabled(!controller->hasNext());
    }
}

void InfoView::setController(InfoController* c) {
    controller = c;
    connect(nameLine, &QLineEdit::textEdited, controller, &InfoController::updateNameOfCurrent);
    connect(previous, &QPushButton::released, controller, &InfoController::prev);
    connect(next, &QPushButton::released, controller, &InfoController::next);
    connect(quitButton, &QPushButton::released, controller, &InfoController::close);
}

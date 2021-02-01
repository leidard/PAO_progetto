#include "organismoinfoview.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QFile>
#include <sstream>



OrganismoInfoView::OrganismoInfoView(QWidget* parent) : QDialog(parent) {
    QFile styleSheetFile(":/style/stylesheetinfo.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    setStyleSheet(styleSheet);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);  //disable "?" button
    setMinimumSize(QSize(280, 210));
    setMaximumSize(QSize(280, 210));
    move(parent->geometry().center());

    layout = new QGridLayout(this);

    // NAME
    nameLine = new QLineEdit(this);
    nameLine->setMaxLength(60);
    nameLine->setReadOnly(true);
    connect(nameLine, &QLineEdit::textEdited, this, [this]() { controller->updateNameOfCurrent(nameLine->text().toStdString()); });
    layout->addWidget(new QLabel("Nome:", this), 0, 0, 1, 1);
    layout->addWidget(nameLine, 0, 1, 1, 2);

    // TYPE
    tipologia = new QLabel("", this);
    layout->addWidget(new QLabel("Tipologia:", this), 1, 0, 1, 1);
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
    connect(previous, &QPushButton::released, this, [this]() { controller->prev(); updateInfo(); });
    connect(next, &QPushButton::released, this, [this]() { controller->next(); updateInfo(); });
    layout->addWidget(previous, 6, 0, 1, 1);
    layout->addWidget(currentmax, 6, 1, 1, 1, Qt::AlignCenter);
    layout->addWidget(next, 6, 2, 1, 1);

    // QUIT
    quitButton = new QPushButton("Chiudi", this);
    connect(quitButton, &QPushButton::released, this, [this]() { killTimer(timerID); QDialog::close(); });
    layout->addWidget(quitButton, 7, 2, 1, 1);

    setLayout(layout);
}

void OrganismoInfoView::closeEvent(QCloseEvent*) {
    killTimer(timerID);
}

void OrganismoInfoView::updateInfo() {
    const Organismo* o = controller->getCurrent();
    if (o == nullptr || (!controller->hasNext() && !controller->hasPrev())) controller->reset();
    if (o == nullptr) {
        setWindowTitle("Info Oganismo");
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
    } else {
        setWindowTitle(("Info oganismo: "+ o->getName()).c_str());
        nameLine->setText(o->getName().c_str());
        nameLine->setReadOnly(false);
        tipologia->setText(QString::fromStdString(o->getSpecie()));
        nutVal->setNum(o->getValoreNutrizionale());
        if(o->isHungry())
            hungry->setText(QString("Sì"));
        else
            hungry->setText(QString("No"));
        if(o->isAwake())
            status->setText(QString("Sveglio"));
        else
            status->setText(QString("Addormentato"));
        staminaBar->setValue(o->getStamina()*100);
        std::stringstream s;
        s << (controller->getPosition() + 1) << " di " << controller->getVectorSize();
        currentmax->setText(s.str().c_str());

        previous->setDisabled(!controller->hasPrev());
        next->setDisabled(!controller->hasNext());
    }
}

void OrganismoInfoView::show() {
    updateInfo();
    startTimer(100);
    QDialog::show();
}

void OrganismoInfoView::setController(Controller* c) {
    controller = c;
}

void OrganismoInfoView::timerEvent(QTimerEvent*) {  //per aggiornare progress bar
    updateInfo();
}

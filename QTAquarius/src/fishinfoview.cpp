#include "fishinfoview.hpp"

FishInfoView::FishInfoView(Controller* c, QWidget *parent) : QDialog(parent), controller(c) {
    timerID = startTimer(100);
    dialog = new QDialog(this);
    dialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);  //disable "?" button
    dialog->setMinimumSize(QSize(350, 250));
    dialog->setMaximumSize(QSize(350, 250));
    QPoint dialogCenter = mapToGlobal(rect().center());
    QPoint parentWindowCenter = parent->window()->mapToGlobal(parent->window()->rect().center());
    move(parentWindowCenter - dialogCenter); //mette la dialog al centro della main window
    displayInfo();
    dialog->setLayout(layout);
    dialog->exec();
}

void FishInfoView::displayInfo(){ //aggiungere i parent ovunque
    layout = new QGridLayout(dialog);
    auto& fishes = controller->getAllFish();

    //ICON
    if(!(fishes.is_empty())){
        if (fishes[0]->getType() == "predatore") {  //draw icon for Predatore
            img = new QLabel(dialog);
            pix = QPixmap(":/images/punto.png");
            pix = pix.scaled(img->size(), Qt::KeepAspectRatio);
            img->setPixmap(pix);
            layout->addWidget(img, 0, 0, 1, 1);
        } else if (fishes[0]->getType() == "preda") {  //draw icon for Preda
            //Immagine pesce
            img = new QLabel(dialog);
            pix = QPixmap(":/images/punto.png");
            pix = pix.scaled(img->size(), Qt::KeepAspectRatio);
            img->setPixmap(pix);
            layout->addWidget(img, 0, 0, 1, 1);
        }

        //NAME
        QString name((fishes[0]->getName()).c_str());
        nameLine = new QLineEdit(dialog);
        nameLine->setMaxLength(30);
        nameLine->setText(name);
        layout->addWidget(new QLabel("Nome:"), 0, 1, 1, 1);
        layout->addWidget(nameLine, 0, 2, 1, 1);
        connect(nameLine, &QLineEdit::textEdited, this, [=](){ saveName(nameLine->text());});

        //TYPE
        layout->addWidget(new QLabel("Tipologia:"), 1, 0, 1, 1);
        QString type((fishes[0]->getType()).c_str());
        tipologia = new QLabel(type, dialog);
        layout->addWidget(tipologia, 1, 1, 1, 1);

        //NUTRITIONAL VALUE
        QString nutritional = QString::number(fishes[0]->getValoreNutrizionale());
        nutVal = new QLabel(nutritional, dialog);
        layout->addWidget(new QLabel("Valore nutrizionale:"), 2, 0, 1, 1);
        layout->addWidget(nutVal, 2, 1, 1, 1);

        //STATUS
        status = new QLabel("alive", dialog);
        layout->addWidget(new QLabel("Status: "), 3, 0, 1, 1);
        layout->addWidget(status, 3, 1, 1, 1);

        //STAMINA BAR
        bar = new QProgressBar(dialog);
        bar->setMaximum(100);
        bar->setValue(fishes[0]->getStamina().getVal());
        connect(bar, &QProgressBar::valueChanged, this, &FishInfoView::dead);
        layout->addWidget(new QLabel("Stamina:"), 4, 0, 1, 1);
        layout->addWidget(bar, 4, 1, 1, 2);

        //PRECEDENTE SUCCESSIVO
        previous = new QPushButton("Precedente", dialog);
        currentmax = new QLabel("0 di" + QString::number(fishes.size()-1), dialog);
        next = new QPushButton("Successivo", dialog);
        connect(previous, &QPushButton::released, this, [=](){ previousFish();});
        connect(next, &QPushButton::released, this, [=](){ nextFish();});
        layout->addWidget(previous, 5, 0, 1, 1);
        layout->addWidget(currentmax, 5, 1, 1, 1);
        layout->addWidget(next, 5, 2, 1, 1);

        //QUIT BUTTON
        quitButton = new QPushButton("Chiudi", dialog);
        connect(quitButton, &QPushButton::released, this, &FishInfoView::close);
        layout->addWidget(quitButton, 6, 2, 1, 1);

    }else{ //there are no fish
        img = new QLabel(dialog);
        pix = QPixmap(":/images/sad.png");
        pix = pix.scaled(img->size(), Qt::KeepAspectRatio);
        img->setPixmap(pix);
        layout->addWidget(img, 0, 0, 1, 1);
        layout->addWidget(new QLabel("Non ci sono pesci"), 0, 1, 1, 1);
    }

}


void FishInfoView::updateInfo(const unsigned int i){
    auto& fishes = controller->getAllFish();

    //ICON
    if (fishes[i]->getType() == "predatore") {  //draw icon for Predatore
        pix = QPixmap(":/images/punto.png");
        pix = pix.scaled(img->size(), Qt::KeepAspectRatio);
//        img->setPixmap(pix); serve?
    } else if (fishes[i]->getType() == "preda") {  //draw icon for Preda
        //Immagine pesce
        pix = QPixmap(":/images/punto.png");
        pix = pix.scaled(img->size(), Qt::KeepAspectRatio);
//        img->setPixmap(pix); serve?
    }

    //NAME
    nameLine->setText(QString((fishes[i]->getName()).c_str()));
    connect(nameLine, &QLineEdit::textEdited, this, [=](){ saveName(nameLine->text(),i);});

    //TYPE
    tipologia->setText(QString((fishes[i]->getType()).c_str()));

    //NUTRITIONAL VALUE
    nutVal->setText(QString::number(fishes[0]->getValoreNutrizionale()));

    //STATUS
    status->setText("alive");

    //STAMINA BAR
    bar->setValue(fishes[i]->getStamina().getVal());

    //PRECEDENTE SUCCESSIVO
    currentmax->setText(QString::number(i) + " di " + QString::number(fishes.size()-1));
    connect(previous, &QPushButton::released, this, [=](){ previousFish(i);});
    connect(next, &QPushButton::released, this, [=](){ nextFish(i);});
}

void FishInfoView::saveName(const QString& n, const unsigned int i){
    auto& fishes = controller->getAllFish();
    fishes[i]->setName(n.toStdString());
}

void FishInfoView::previousFish(const unsigned int i){
    if(i>0) updateInfo(i-1);
}

void FishInfoView::nextFish(const unsigned int i){
    auto& fishes = controller->getAllFish();
    if(i<fishes.size()-1) updateInfo(i+1);
}

void FishInfoView::dead(){
    if (bar->value()==0) status->setText("morto");
}

void FishInfoView::close(){
    dialog->close();
}

void FishInfoView::timerEvent(const QTimerEvent *event){ //aggiorna la progress bar con la stamina
    auto& fishes= controller->getAllFish();
    bar->setValue(fishes[0]->getStamina().getVal());
}


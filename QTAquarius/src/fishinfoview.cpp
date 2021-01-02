#include "fishinfoview.hpp"

FishInfoView::FishInfoView(QWidget *parent) : QDialog(parent) {
    timerID = startTimer(100);
    int i=0; //i è da passare come param a openInfo() ed è il numero del pesce nell'array pesci
    dialog = new QDialog(parent);
    dialog->setWindowTitle("Info");
    dialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //disable "?" button

    grid = new QGridLayout(dialog);

    auto& fishes = controller->getAllFish();
    //ICON
    if (fishes[i]->getType() == "predatore"){ //draw icon for Predatore
        img = new QLabel(dialog);
        QPixmap pix = QPixmap(":/images/punto.png");
        pix = pix.scaled(img->size(),Qt::KeepAspectRatio);
        img->setPixmap(pix);
        grid->addWidget(img,0,0,1,1);
    } else if (fishes[i]->getType() == "preda"){ //draw icon for Preda
        //Immagine pesce
        img = new QLabel(dialog);
        QPixmap pix = QPixmap(":/images/punto.png");
        pix = pix.scaled(img->size(),Qt::KeepAspectRatio);
        img->setPixmap(pix);
        grid->addWidget(img,0,0,1,1);
    }

    //NAME
    QString name((fishes[i]->getName()).c_str());
    nameLine = new QLineEdit(dialog);
    nameLine->setMaxLength(30);
    nameLine->setText(name);
    grid->addWidget(new QLabel("Nome:"), 0, 1, 1,1);
    grid->addWidget(nameLine, 0, 2, 1,1);
    connect(nameLine, SIGNAL(textEdited(QString)), this, SLOT(saveInfo(QString)));

    //TYPE
    QString type((fishes[i]->getType()).c_str());
    grid->addWidget(new QLabel("Tipologia:"), 1, 0, 1,1);
    grid->addWidget(new QLabel(type), 1, 1, 1, 1 );

//    //NUTRITIONAL VALUE
//    QString nutVal = QString::number(fishes[i]->getValoreNutrizionale());
//    grid->addWidget(new QLabel("Valore nutrizionale:"), 2, 0, 1,1);
//    grid->addWidget(new QLabel(nutVal), 2, 1, 1, 1 );

    //STATUS
    status = new QLabel("alive");
    grid->addWidget(new QLabel("Status: "), 2, 0, 1,1);
    grid->addWidget(status, 2, 1, 1, 1 );

    //STAMINA BAR
    bar = new QProgressBar(dialog);
    bar->setMaximum(10);
    double val = fishes[0]->getStamina().getVal();
    bar->setValue(val);
    connect(bar, SIGNAL(valueChanged(int)), this, SLOT(dead()));
    grid->addWidget(new QLabel("Stamina:"), 3, 0, 1, 1);
    grid->addWidget(bar, 3, 1, 1, 2);

    //SAVE BUTTON (?)
    saveButton = new QPushButton("Salva", dialog);
    grid->addWidget(saveButton, 4, 0, 1, 1);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveInfo(i)));

    //QUIT BUTTON
    quitButton = new QPushButton("Chiudi", dialog);
    connect(quitButton, SIGNAL(released()), this, SLOT(close()));


    grid->addWidget(quitButton, 4, 1, 1, 1);
    dialog->setLayout(grid);
    dialog->resize(400,400);
    dialog->exec();
}


void FishInfoView::saveInfo(QString* n){
    std::cout<<"SAVE";
    auto& fishes = controller->getAllFish();
    fishes[0]->setName(n->toStdString());
}

void FishInfoView::dead(){
    if (bar->value()==0) status->setText("morto");
}

void FishInfoView::close(){
    dialog->close();
}

void FishInfoView::timerEvent(QTimerEvent *event){
    auto& fishes= controller->getAllFish();
    double val = fishes[0]->getStamina().getVal();
    bar->setValue(val);
}

void FishInfoView::setController(Controller *c) {
    controller = c;
}

#ifndef FISHINFO_HPP
#define FISHINFO_HPP
#include <QCloseEvent>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QPointer>
#include <QProgressBar>
#include <QPushButton>
#include <QResizeEvent>
#include <QString>
#include <QTimerEvent>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QSlider>
#include <QSignalMapper>
#include <iostream>

#include "controller.hpp"
#include "deepptr.hpp"
#include "fish.hpp"
#include "preda.hpp"
#include "predatore.hpp"
#include "vect2d.hpp"
#include "vector.hpp"

class FishInfoView : public QDialog {
Q_OBJECT
   public:
    FishInfoView(Controller* c, QWidget* parent = nullptr);
    void displayInfo();
    void updateInfo(const unsigned int);
    void timerEvent(const QTimerEvent* event);


   private:
    QDialog* dialog;
    Controller* controller;
    int timerID;
    QGridLayout* layout;    //Layout
    QLabel* img;          //Icon
    QPixmap pix;
    QLineEdit* nameLine;  //Fish's name
    QLabel* tipologia;
    QLabel* nutVal;
    QProgressBar* bar;  //Stamina
    QLabel* status;
    QLabel* currentmax;
    //QSlider* slider;
    QPushButton* previous;
    QPushButton* next;
    QPushButton* saveButton;
    QPushButton* quitButton;

   private slots:
    void close();
    void saveName(const QString&, const unsigned int = 0);
    void previousFish(const unsigned int = 0);
    void nextFish(const unsigned int = 0);
//    void onSliderMoved(int);
    void dead();
};

#endif  // FISHINFO_HPP

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
#include <QSignalMapper>
#include <QSlider>
#include <QString>
#include <QTimerEvent>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>
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
    FishInfoView(QWidget* parent = nullptr);
    void show();
    void setController(Controller* c);

   private:
    Controller* controller;
    Vector<DeepPtr<Fish>>::iterator pos;
    void timerEvent(QTimerEvent* event);
    void updateInfo();
    void closeEvent(QCloseEvent* event);

    int timerID;
    QGridLayout* layout;  //Layout
    QLabel* img;          //Icon
    QLineEdit* nameLine;  //Fish's name
    QLabel* tipologia;
    QLabel* nutVal;
    QProgressBar* bar;  //Stamina
    QLabel* currentmax;
    QPushButton* previous;
    QPushButton* next;
    QPushButton* saveButton;
    QPushButton* quitButton;
};

#endif  // FISHINFO_HPP

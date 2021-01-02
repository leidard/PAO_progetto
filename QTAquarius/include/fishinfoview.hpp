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
#include <iostream>

#include "controller.hpp"
#include "deepptr.hpp"
#include "fish.hpp"
#include "preda.hpp"
#include "predatore.hpp"
#include "vect2d.hpp"

class FishInfoView : public QDialog {
    Q_OBJECT
   public:
    FishInfoView(QWidget* parent = nullptr);
    void timerEvent(QTimerEvent* event);

   private:
    // addClass(QWidget *parent = 0);
    void setController(Controller* c);

    QDialog* dialog;
    Controller* controller;
    int timerID;
    QGridLayout* grid;    //Layout
    QLabel* img;          //Icon
    QLineEdit* nameLine;  //Fish's name
    QLabel* status;
    QProgressBar* bar;  //Stamina
    QPushButton* saveButton;
    QPushButton* quitButton;

   private slots:
    void close();
    void saveInfo(QString*);
    void dead();
};

#endif  // FISHINFO_HPP

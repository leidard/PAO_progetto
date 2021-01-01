#ifndef FISHINFO_HPP
#define FISHINFO_HPP
#include "controller.hpp"
#include "predatore.hpp"
#include "preda.hpp"
#include "deepptr.hpp"
#include "fish.hpp"
#include "vect2d.hpp"


#include <iostream>
#include <QWidget>
#include <QDialog>
#include <QPointer>
#include <QPaintEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QToolBar>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QString>
#include <QLabel>
#include <QPixmap>
#include <QProgressBar>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QCloseEvent>
#include <QTimerEvent>

class FishInfoView : public QDialog{
Q_OBJECT
    public:
        FishInfoView(QWidget *parent = nullptr);
        void timerEvent(QTimerEvent *event);

    private:
        addClass(QWidget *parent = 0);
        void setController(Controller* c);

        QDialog* dialog;
        Controller* controller;
        int timerID;
        QGridLayout* grid; //Layout
        QLabel* img; //Icon
        QLineEdit* nameLine; //Fish's name
        QLabel* status;
        QProgressBar* bar; //Stamina
        QPushButton* saveButton;
        QPushButton* quitButton;

    private slots:
        void close();
        void saveInfo(QString*);
        void dead();
};

#endif // FISHINFO_HPP

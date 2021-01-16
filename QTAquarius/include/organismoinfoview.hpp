#include <QDialog>

#include "controller.hpp"

#ifndef ORGANISMOINFO_HPP
#define ORGANISMOINFO_HPP

class QWidget;
class QLabel;
class QLineEdit;
class QGridLayout;
class QProgressBar;
class QPushButton;
class QCloseEvent;
class QTimerEvent;

class OrganismoInfoView : public QDialog {
    Q_OBJECT
   public:
    OrganismoInfoView(QWidget* parent = nullptr);
    void show();
    void setController(Controller*);

   private:
    void updateInfo();

    Controller* controller;
    Vector<DeepPtr<Organismo>>::iterator pos;

    void timerEvent(QTimerEvent*);
    void closeEvent(QCloseEvent*);

    int timerID;
    QGridLayout* layout;  //Layout
    QLabel* img;          //Icon
    QLineEdit* nameLine;  //Organismo's name
    QLabel* tipologia;
    QLabel* nutVal;
    QProgressBar* bar;  //Stamina
    QLabel* currentmax;
    QPushButton* previous;
    QPushButton* next;
    QPushButton* saveButton;
    QPushButton* quitButton;
};

#endif  // ORGANISMOINFO_HPP

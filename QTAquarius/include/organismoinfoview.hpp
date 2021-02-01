#include <QDialog>

#include "controller.hpp"
#include "organismo.hpp"
#include "sardina.hpp"
#include "tonno.hpp"
#include "phytoplankton.hpp"

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
    QGridLayout* layout;        //Layout
    QLineEdit* nameLine;        //Organismo's name
    QLabel* tipologia;          //Species
    QLabel* nutVal;             //Nutritional value
    QLabel* hungry;             //Hungry or not
    QLabel* status;             //Awake/asleep
    QProgressBar* staminaBar;   //Stamina
    QLabel* currentmax;
    QPushButton* previous;
    QPushButton* next;
    QPushButton* saveButton;
    QPushButton* quitButton;
};

#endif  // ORGANISMOINFO_HPP

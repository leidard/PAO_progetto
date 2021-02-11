#include <QDialog>

#ifndef INFOVIEW_HPP
#define INFOVIEW_HPP

class QWidget;
class QLabel;
class QLineEdit;
class QGridLayout;
class QProgressBar;
class QPushButton;
class InfoController;
class Organismo;

class InfoView : public QDialog {
    Q_OBJECT
public:
    InfoView(QWidget* parent = nullptr);
    void setController(InfoController*);
    void setData(Organismo* = nullptr);

private:
    InfoController* controller;

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

#endif

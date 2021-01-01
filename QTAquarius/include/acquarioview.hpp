#include "controller.hpp"
#include "fishinfoview.hpp"

#ifndef ACQUARIOVIEW_H
#define ACQUARIOVIEW_H

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


class AcquarioView : public QWidget
{
    Q_OBJECT
private:
    Controller* controller;
    FishInfoView* infoView;
    QDialog* dialog;
    QLineEdit* nameLine;
    QProgressBar* bar;
    QLabel* status;
    int timerID;
//    QPointer<QAction> fileSalva;
//    QPointer<QAction> fileCarica;

public:
    explicit AcquarioView(QWidget *parent = nullptr);
   // void buildMenu
    void setController(Controller* c);
    void resizeEvent(QResizeEvent *event) override;

protected:
    void paintEvent(QPaintEvent* event) override;
    void timerEvent(QTimerEvent *event);

private slots:
    void openInfo();
    void close();
    void saveInfo();
    void dead();
};

#endif // ACQUARIOVIEW_H

#include "controller.hpp"
#include "fishinfoview.hpp"

#ifndef ACQUARIOVIEW_H
#define ACQUARIOVIEW_H

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

class AcquarioView : public QWidget {
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
    explicit AcquarioView(QWidget* parent = nullptr);
    // void buildMenu
    void setController(Controller* c);
    void resizeEvent(QResizeEvent* event) override;

   protected:
    void paintEvent(QPaintEvent* event) override;

   private slots:
    void openInfo();
    void close();
    void saveInfo();
    void dead();
};

#endif  // ACQUARIOVIEW_H

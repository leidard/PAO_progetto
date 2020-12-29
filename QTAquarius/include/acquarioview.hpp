#include "controller.hpp"

#ifndef ACQUARIOVIEW_H
#define ACQUARIOVIEW_H

#include <QWidget>

class AcquarioView : public QWidget
{
    Q_OBJECT
private:
    Controller* controller;
public:
    explicit AcquarioView(QWidget *parent = nullptr);

    void setController(Controller* c);
    void resizeEvent(QResizeEvent *event) override;
protected:
    void paintEvent(QPaintEvent* event) override;

signals:
};

#endif // ACQUARIOVIEW_H

#include "acquarioview.h"

#include <QApplication>
#include "controller.hpp"
#include "middlewares/fishcreator.hpp"
#include "aquarius.hpp"
#include "vect2d.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AcquarioView view;
    Aquarius::init();
    Aquarius* model = Aquarius::getInstance();
    Controller c;
    c.setModel(model);
    c.addPredatore(Vect2D(100,100));
    c.setView(&view);
    view.setController(&c);
    view.show();
    c.start();
    return a.exec();
}

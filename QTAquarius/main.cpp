#include "acquarioview.hpp"

#include <QApplication>
#include "controller.hpp"
#include "middlewares/fishcreator.hpp"
#include "aquarius.hpp"
#include "vect2d.hpp"
#include <cstdlib>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AcquarioView view;
    Aquarius::init();
    Aquarius* model = Aquarius::getInstance();
    Controller c;
    c.setModel(model);
    for (int i=0; i<100; i++) c.addPredatore(Vect2D(100 + std::rand()%300,100+std::rand()%200));
    c.setView(&view);
    view.setController(&c);
    view.show();
    c.start();
    return a.exec();
}

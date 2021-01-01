#include <QApplication>
#include <cstdlib>
#include <iostream>

#include "acquarioview.hpp"
#include "aquarius.hpp"
#include "bsptree.hpp"
#include "controller.hpp"
#include "middlewares/fishcreator.hpp"
#include "predatore.hpp"
#include "vect2d.hpp"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    BSPTree<Fish> t(Range(100, 100));

    Predatore* p = new Predatore[3]{
        Predatore(Vect2D(10, 10), "giorgio"),
        Predatore(Vect2D(60, 10)),
        Predatore(Vect2D(80, 80))};


    std::cout << t.insert(p[0].getPosition(), p) << std::endl;
    std::cout << t.insert(p[1].getPosition(), p + 1) << std::endl;
    std::cout << t.insert(p[2].getPosition(), p + 2) << std::endl;

    std::cout << t.click(15, 15, 10)->getName() << std::endl;
    std::cout << p->getName() << std::endl;
    std::cout << (p+1)->getName() << std::endl;
    std::cout << (p+2)->getName() << std::endl;
    return 0;

    AcquarioView view;
    Aquarius model;
    Controller c;
    c.setModel(&model);
    for (int i = 0; i < 100; i++) c.addPredatore(Vect2D(100 + std::rand() % 300, 100 + std::rand() % 200));
    c.setView(&view);
    view.setController(&c);
    view.show();
    c.start();
    return a.exec();
}

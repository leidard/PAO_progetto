#include <QApplication>
#include <cstdlib>
#include <iostream>

#include "acquarioview.hpp"
#include "aquarius.hpp"
#include "controller.hpp"
#include "fish.hpp"
#include "fishinfoview.hpp"
#include "predatore.hpp"
#include "vect2d.hpp"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    AcquarioView view;
    Aquarius model;
    Controller c;
    c.setModel(&model);
    for (int i = 0; i < 10; i++) c.addPredatore(Vect2D(100 + std::rand() % 300, 100 + std::rand() % 200));
    for (int i = 0; i < 10; i++) c.addPreda(Vect2D(100 + std::rand() % 300, 100 + std::rand() % 200));

    c.setView(&view);
    view.setController(&c);
    view.show();
    c.start();
    return a.exec();
}

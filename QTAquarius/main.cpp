#include <QApplication>
#include <QFile>

#include "acquarioview.hpp"
#include "aquarius.hpp"
#include "controller.hpp"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    AcquarioView view;
    Aquarius model;
    Controller c;
    c.setModel(&model);
    c.setView(&view);
    view.setController(&c);
    view.show();
    c.start();
    return a.exec();
}

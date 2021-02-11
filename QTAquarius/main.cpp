#include <QApplication>
#include <QFile>

#include "acquarioview.hpp"
#include "infoview.hpp"
#include "aquarius.hpp"
#include "controller.hpp"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    AcquarioView view;
    InfoView infoview(&view);
    Aquarius model;
    Controller c;
    InfoController ic;
    c.setInfoController(&ic);
    c.setModel(&model);
    c.setView(&view);
    c.setInfoView(&infoview);
    view.setController(&c);
    infoview.setController(&ic);
    view.show();
    c.start();
    return a.exec();
}

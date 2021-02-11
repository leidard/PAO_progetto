#include <QApplication>
#include <QFile>

#include "acquarioview.hpp"
#include "organismoinfoview.hpp"
#include "aquarius.hpp"
#include "controller.hpp"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    AcquarioView view;
    OrganismoInfoView infoview(&view);
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

#include <QObject>

#ifndef INFOCONTROLLER_H
#define INFOCONTROLLER_H

class Organismo;
class QTimer;
class Aquarius;
class AcquarioView;
class QMouseEvent;
class InfoView;
class QString;

class InfoController : public QObject {
    Q_OBJECT

private:
    Aquarius* _model;
    InfoView* _view;
    QTimer* _timer;

    unsigned int pos;

public:
    InfoController();
    ~InfoController();

    void setModel(Aquarius*);
    void setView(InfoView*);

    bool isVisible() const;

    unsigned int getSize() const;
    unsigned int getPosition() const;
    Organismo* getCurrent() const;

    bool hasNext() const;
    bool hasPrev() const;



public slots:
    void show();
    void close();

    void tick();

    void next();
    void prev();

    void updateNameOfCurrent(const QString&);
};

#endif
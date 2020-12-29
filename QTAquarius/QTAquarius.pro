QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH = include/

SOURCES += \
    main.cpp \
    src/acquarioview.cpp \
    src/aquarius.cpp \
    src/cartesianobject2d.cpp \
    src/controller.cpp \
    src/daycycle.cpp \
    src/fish.cpp \
    src/food.cpp \
    src/predatore.cpp \
    src/saverloader.cpp \
    src/stamina.cpp \
    src/vect2d.cpp \
    src/vegetale.cpp \
    src/vehicle.cpp

HEADERS += \
    include/acquarioview.hpp \
    include/aquarius.hpp \
    include/cartesianobject2d.hpp \
    include/controller.hpp \
    include/daycycle.hpp \
    include/deepptr.hpp \
    include/fish.hpp \
    include/food.hpp \
    include/middlewares/fishcreator.hpp \
    include/middlewares/foodcreator.hpp \
    include/middlewares/saverloader.hpp \
    include/preda.hpp \
    include/predatore.hpp \
    include/stamina.hpp \
    include/vect2d.hpp \
    include/vector.hpp \
    include/vegetale.hpp \
    include/vehicle.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

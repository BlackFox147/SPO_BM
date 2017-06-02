QT -= core app
QT += network
TARGET = Server_1
CONFIG += console
TEMPLATE = app
SOURCES += \
    listofcli.cpp \
    main.cpp \
    infofile.cpp \
    listofinfofile.cpp \
    connect.cpp

HEADERS += \
    listofcli.h \
    infofile.h \
    listofinfofile.h \
    connect.h

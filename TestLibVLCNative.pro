QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testVlc
TEMPLATE = app

CONFIG += c++11

DEPENDPATH += .

win32 {
    QMAKE_LFLAGS = -static-libgcc -static-libstdc++
}

LIBS += -lvlc -lX11

# Input
HEADERS +=
SOURCES += main.cpp
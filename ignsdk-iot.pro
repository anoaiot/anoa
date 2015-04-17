#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T03:20:55
#
#-------------------------------------------------

QT       += network core websockets sql printsupport serialport webchannel

QT       -= gui

TARGET = ignsdk-iot
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES +=  src/main.cpp \
            src/ignws.cpp \
            src/ignwstrans.cpp \
    src/ignserial.cpp \
    src/ignnetwork.cpp \
    src/ignfs.cpp \
    src/ignsql.cpp

HEADERS  += src/ignws.h \
            src/ignwstrans.h \
    src/ignserial.h \
    src/ignjson.h \
    src/ignnetwork.h \
    src/ignfs.h \
    src/ignsql.h \
    src/version.h

OBJECTS_DIR = ../ignsdk-iot-bin/build
MOC_DIR = ../ignsdk-iot-bin/build
DESTDIR = ../ignsdk-iot-bin/bin

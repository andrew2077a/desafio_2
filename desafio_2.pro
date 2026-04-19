TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        estadistica.cpp \
        fecha.cpp \
        grupo.cpp \
        jugador.cpp \
        lector_archivo.cpp \
        lista.cpp \
        main.cpp \
        partido.cpp \
        simulador.cpp \
        torneo.cpp

HEADERS += \
    estadistica.h \
    fecha.h \
    grupo.h \
    jugador.h \
    libreria.h \
    lista.h \
    partido.h \
    simulador.h \
    torneo.h

DISTFILES += \
    selecciones_clasificadas_mundial.csv

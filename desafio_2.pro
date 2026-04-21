TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Estadistica.cpp \
        Fecha.cpp \
        Grupo.cpp \
        Jugador.cpp \
        Lista.cpp \
        Partido.cpp \
        Simulador.cpp \
        lector_archivo.cpp \
        main.cpp \
        torneo.cpp

HEADERS += \
    Estadistica.h \
    Fecha.h \
    Grupo.h \
    Jugador.h \
    Lista.h \
    Partido.h \
    Simulador.h \
    libreria.h \
    torneo.h

DISTFILES += \
    selecciones_clasificadas_mundial.csv

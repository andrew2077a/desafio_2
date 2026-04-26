TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Equipo.cpp \
        Estadistica.cpp \
        Fecha.cpp \
        Grupo.cpp \
        Jugador.cpp \
        Lista.cpp \
        Partido.cpp \
        Simulador.cpp \
        lector_archivo.cpp \
        main.cpp \
        metricas.cpp \
        torneo.cpp

HEADERS += \
    Equipo.h \
    Estadistica.h \
    Fecha.h \
    Grupo.h \
    Jugador.h \
    Lista.h \
    Partido.h \
    Simulador.h \
    libreria.h \
    metricas.h \
    torneo.h

DISTFILES += \
    selecciones_clasificadas_mundial.csv

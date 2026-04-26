#ifndef GRUPO_H
#define GRUPO_H

#include "Equipo.h"
#include "Partido.h"
#include "Fecha.h"

class Grupo {
private:
    char letra;
    Equipo* equipos[4];
    Partido* partidos[6];

public:
    Grupo();
    void generarFixture(Fecha fechaInicio);
    void jugarPartidos();
    void obtenerTablaPosiciones();
    Lista<Equipo*> obtenerMejoresTerceros();
};

#endif


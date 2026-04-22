#ifndef GRUPO_H
#define GRUPO_H
#include "Equipo.h"

class Grupo{
private:
    char letra;
    equipo* equipos[4];
    partido* partidos[6];

public:
    Grupo();
    generarFixture(Fecha fechaInicio);
    void jugarPartidos();
    void obtenerTablaPosiciones();
    Equipo*[] obtenerMejoresTerceros();

};

#endif // GRUPO_H

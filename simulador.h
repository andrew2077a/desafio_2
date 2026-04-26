#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Equipo.h"

class Simulador {
public:
    static float golesEsperados(const Equipo& atacante, const Equipo& defensor);
    static unsigned short int generarGoles(float lambda);
    static float calcularPosesion(const Equipo& local, const Equipo& visitante);
    static const Equipo& desempatarPorRanking(const Equipo& local, const Equipo& visitante);

    // Probabilidades (podrían ser inline)
    static bool recibeAmarilla();
    static bool recibeSegundaAmarilla();
    static bool recibeRoja();
    static bool cometeFalta(unsigned short int faltasActuales);
};

#endif

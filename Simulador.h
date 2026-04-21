#ifndef SIMULADOR_H
#define SIMULADOR_H

class Simulador{
public:
    Simulador();
    static double golesEsperados( Equipo local, Equipo visitante);
    static double asignarGolesJugadores( Partido partido , int golesEquipo, bool esLocal);
    static double aplicarTarjetasYFaltas( Partido partido, ListaJugador* jugadores);
    static float calcularPosesion( Equipo local ,  Equipo visitante);
    static equipo* desempatarPorRanking(Equipo local ,  Equipo visitante);
};

#endif // SIMULADOR_H

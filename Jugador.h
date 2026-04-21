#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
class Jugador{
private:
    string nombre;
    string apellido;
    int numeroCamiseta;
    Estadisticas estadisticas;
public:
    Jugador();

    void actualizarEstadisticas(Partido partido, int minutos);
    void acumularGoles(int goles);
    acumularTarjetas(int amarillas, int rojas);

};

#endif // JUGADOR_H

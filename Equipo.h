#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "Estadistica.h"
#include "Lista.h"
#include "Jugador.h"
// No incluimos Partido.h aquí para evitar recursividad (Círculo de dependencias)
class Partido;

using namespace std;

class Equipo {
private:
    string nombrePais;
    string confederacion;
    int rankingFIFA;
    string directorTecnico;
    Estadistica estadisticasHist;
    Lista<Jugador*>* plantilla;

public:
    Equipo();
    Equipo(string nombre, string conf, int ranking, string dt);
    ~Equipo();

    void actualizarEstadisticas(Partido* partido);
    Lista<Jugador*>* obtenerGoleadores();

    float obtenerPromedioGolesFavor() const;
    float obtenerPromedioGolesContra() const;
    string getNombre() const;
    int getRanking() const;

    void agregarJugador(Jugador* j);
};

#endif

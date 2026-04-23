#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "Estadistica.h"
#include "Lista.h"
#include "Jugador.h"

class Partido;

using namespace std;

class Equipo {
private:
    string nombrePais;
    string confederacion;
    unsigned short int rankingFIFA; // Tipo unificado
    string directorTecnico;
    Estadistica estadisticasHist;
    Lista<Jugador*> plantilla; // CAMBIO: Objeto directo, no puntero

public:
    Equipo();
    Equipo(string nombre, string conf, unsigned short int ranking, string dt);
    ~Equipo(); // Ahora está casi vacío porque no hay 'new'

    void actualizarEstadisticas(Partido* partido);

    // CAMBIO: Retorno por valor (RVO) y const-correctness
    Lista<Jugador*> obtenerGoleadores() const;

    float obtenerPromedioGolesFavor() const;
    float obtenerPromedioGolesContra() const;
    string getNombre() const;
    int getRanking() const;

    void agregarJugador(Jugador* j);
};

#endif

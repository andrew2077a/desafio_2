#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "Estadistica.h"
#include "Lista.h"
#include "Jugador.h"

class Equipo {
private:
    std::string nombrePais;
    std::string confederacion;
    unsigned short int rankingFIFA;
    std::string directorTecnico;
    Estadistica estadisticasHist;
    Lista<Jugador*> plantilla;  // <-- almacenamos punteros

    Equipo(const Equipo&);
    Equipo& operator=(const Equipo&);

public:
    Equipo();
    Equipo(const std::string& nombre, const std::string& conf,
           unsigned short int ranking, const std::string& dt);
    ~Equipo();

    std::string getNombre() const;
    std::string getConfederacion() const;
    unsigned short int getRanking() const;
    const Estadistica& getEstadisticas() const;

    void setEstadisticasHistoricas(const Estadistica& stats);

    float obtenerPromedioGolesFavor() const;
    float obtenerPromedioGolesContra() const;

    Lista<Jugador*> obtenerGoleadores() const;   // <-- devuelve lista de punteros

    void agregarJugador(Jugador* j);
    unsigned short int obtenerJugadores(Jugador* destino[], unsigned short int max) const;
    Jugador* obtenerJugadorPorNumero(unsigned short int numero) const;
    Jugador* obtenerJugadorPorIndice(unsigned short int indice) const;

    void actualizarEstadisticas(const Estadistica& statsPartido);
};

#endif

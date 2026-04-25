#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "Estadistica.h"
#include "Lista.h"
#include "Jugador.h"

class Equipo
{
private:
    std::string nombrePais;
    std::string confederacion;
    unsigned short int rankingFIFA;
    std::string directorTecnico;
    Estadistica estadisticasHist;
    Lista<Jugador*> plantilla;

    Equipo(const Equipo&);//--->No copiar
    Equipo& operator=(const Equipo&);

public:
    // Constructores
    Equipo();
    Equipo(const std::string& nombre, const std::string& conf,
           unsigned short int ranking, const std::string& dt);

    // Destructor (libera jugadores)
    ~Equipo();

    // Getters
    std::string getNombre() const;
    unsigned short int getRanking() const;
    const Estadistica& getEstadisticas() const;
    float obtenerPromedioGolesFavor() const;
    float obtenerPromedioGolesContra() const;
    Lista<Jugador*> obtenerGoleadores() const;

    // Setters
    void agregarJugador(Jugador* j);

    // recibe Estadistica
    void actualizarEstadisticas(const Estadistica& statsPartido);
};

#endif

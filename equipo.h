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

    Lista<Jugador*> plantilla;

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


    // Nuevo método: llena un array con hasta 'max' jugadores - Retorna la cantidad real de jugadores copiados
    unsigned short int obtenerJugadores(Jugador* destino[], unsigned short int max) const;

    // Obtener jugador por número de camiseta (útil para convocados)
    Jugador* obtenerJugadorPorNumero(unsigned short int numero) const;
};

#endif

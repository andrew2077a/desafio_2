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
    Lista<Jugador*> plantilla;
    
    Equipo(const Equipo&);
    Equipo& operator=(const Equipo&);
    
public:
    Equipo();
    Equipo(const std::string& nombre, const std::string& conf, 
           unsigned short int ranking, const std::string& dt);
    ~Equipo(); 
    
    void actualizarEstadisticas(const Estadistica& statsPartido);
    
    Lista<Jugador*> obtenerGoleadores() const;
    
    float obtenerPromedioGolesFavor() const;
    float obtenerPromedioGolesContra() const;
    
    std::string getNombre() const;
    unsigned short int getRanking() const;
    
    void agregarJugador(Jugador* j);
};

#endif

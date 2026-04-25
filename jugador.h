#ifndef JUGADOR_H
#define JUGADOR_H
#include "estadistica.h"
#include <string>

class Jugador
{
private:
    std::string nombre;
    std::string apellido;
    unsigned short int numeroCamiseta;
    Estadistica estadisticas;

public:
    //Constructor
    Jugador(const std::string& nombre, const std::string& apellido, unsigned short int numeroCamiseta);

    // Getters
    std::string getNombre() const;
    std::string getApellido() const;
    unsigned short int getNumeroCamiseta() const;
    const Estadistica& getEstadisticas() const;
    unsigned short int getGoles() const;

    // estadisticas que hizo en el partido
    void actualizarEstadisticas(const Estadistica& statsPartido);
};

#endif // JUGADOR_H

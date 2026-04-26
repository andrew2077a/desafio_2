#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "Estadistica.h"

class Jugador
{
private:
    std::string nombre;
    std::string apellido;
    unsigned short int numeroCamiseta;
    Estadistica estadisticas;

    Jugador(const Jugador&);//<--No copia
    Jugador& operator=(const Jugador&);

public:
    // Constructor
    Jugador(const std::string& nombre, const std::string& apellido,
            unsigned short int numeroCamiseta);

    // Destructor
    ~Jugador();

    // Getters
    std::string getNombre() const;
    std::string getApellido() const;
    unsigned short int getNumeroCamiseta() const;
    const Estadistica& getEstadisticas() const;
    unsigned short int getGoles() const;
    std::string getNombreCompleto() const;

    // Setter
    void actualizarEstadisticas(const Estadistica& statsPartido);
};

#endif

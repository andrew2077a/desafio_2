#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "Estadistica.h"

using namespace std;

class Partido;

class Jugador {
private:
    string nombre;
    string apellido;
    int numeroCamiseta;
    Estadistica estadisticas; // Objeto directo (Eficiencia de caché)

public:
    jugador();
    Jugador(const string& nom, const string& ape, int num);

    // Métodos de actualización
    void acumularGoles(int goles);
    void acumularTarjetas(int amarillas, int rojas);
    void actualizarEstadisticas(int minutos, int asis, int flts);

    // Getters
    int getGoles() const;
    int getNumero() const;
    string getNombreCompleto() const;
    const Estadistica& getEstadisticas() const; // Retorno por referencia constante
};

#endif

#include "jugador.h"
using namespace std;

// Constructor
Jugador::Jugador(const string& nombre, const string& apellido, unsigned short int numeroCamiseta)
    : nombre(nombre), apellido(apellido), numeroCamiseta(numeroCamiseta), estadisticas() {
    // Todo se inicializa en 0 gracias al constructor de Estadistica
}

// Getters
string Jugador::getNombre() const{
    return nombre;
}

string Jugador::getApellido() const{
    return apellido;
}

unsigned short int Jugador::getNumeroCamiseta() const{
    return numeroCamiseta;
}

const Estadistica& Jugador::getEstadisticas() const{
    return estadisticas;
}

unsigned short int Jugador::getGoles() const {
    return estadisticas.getGolesFavor();
}

// Actualizar estadisticas (acumula las del partido)
void Jugador::actualizarEstadisticas(const Estadistica& statsPartido) {
    estadisticas.actualizar(statsPartido);
}

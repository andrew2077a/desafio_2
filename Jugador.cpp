#include "Jugador.h"
using namespace std;

Jugador::Jugador() : nombre(""), apellido(""), numeroCamiseta(0), estadisticas() {}

// Constructor de copia
Jugador::Jugador(const Jugador& otro)
    : nombre(otro.nombre), apellido(otro.apellido),
    numeroCamiseta(otro.numeroCamiseta), estadisticas(otro.estadisticas) {}

// Operador de asignación
Jugador& Jugador::operator=(const Jugador& otro) {
    if (this == &otro) return *this;
    nombre = otro.nombre;
    apellido = otro.apellido;
    numeroCamiseta = otro.numeroCamiseta;
    estadisticas = otro.estadisticas;
    return *this;
}

// Constructor
Jugador::Jugador(const string& nombre, const string& apellido, unsigned short int numeroCamiseta)
    : nombre(nombre), apellido(apellido),numeroCamiseta(numeroCamiseta), estadisticas() {}

// Destructor (no hay memoria dinamica)
Jugador::~Jugador() {}

// Getters
string Jugador::getNombre() const { return nombre; }
string Jugador::getApellido() const { return apellido; }
unsigned short int Jugador::getNumeroCamiseta() const { return numeroCamiseta; }
const Estadistica& Jugador::getEstadisticas() const { return estadisticas; }
unsigned short int Jugador::getGoles() const { return estadisticas.getGolesFavor(); }
string Jugador::getNombreCompleto() const { return nombre + " " + apellido; }

// Setter
void Jugador::actualizarEstadisticas(const Estadistica& statsPartido){
    estadisticas.actualizar(statsPartido);
}

#include "Jugador.h"

using namespace std;

Jugador::Jugador(const string& nom, const string& ape, int num)
    : nombre(nom), apellido(ape), numeroCamiseta(num), estadisticas() {
    // estadisticas() llama al constructor por defecto que pusiste en 0
}

void Jugador::acumularGoles(int goles) {
    // Creamos un objeto temporal con los goles y lo sumamos
    // Usamos el constructor de Estadistica: Estadistica(gFavor, gContra, PG, PE, PP, TA, TR, Faltas, Min, Asist)
    Estadistica temp(goles, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    estadisticas.actualizar(temp);
}

void Jugador::acumularTarjetas(int amarillas, int rojas) {
    Estadistica temp(0, 0, 0, 0, 0, amarillas, rojas, 0, 0, 0);
    estadisticas.actualizar(temp);
}

void Jugador::actualizarEstadisticas(int minutos, int asis, int flts) {
    Estadistica temp(0, 0, 0, 0, 0, 0, 0, flts, minutos, asis);
    estadisticas.actualizar(temp);
}

int Jugador::getGoles() const {
    return estadisticas.getGolesFavor();
}

int Jugador::getNumero() const {
    return numeroCamiseta;
}

string Jugador::getNombreCompleto() const {
    return nombre + " " + apellido;
}

const Estadistica& Jugador::getEstadisticas() const {
    return estadisticas;
}

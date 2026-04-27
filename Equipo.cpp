#include "Equipo.h"
using namespace std;

//Constructor x defecto
Equipo::Equipo() : nombrePais(""), confederacion(""), rankingFIFA(0), directorTecnico("") {}


//Constructor x parametros
Equipo::Equipo(const string& nombre, const string& conf,
               unsigned short int ranking, const string& dt)
    : nombrePais(nombre), confederacion(conf), rankingFIFA(ranking), directorTecnico(dt) {}


// Destructor
Equipo::~Equipo() {
    for (int i = 0; i < plantilla.obtenerTamanio(); ++i) {
        delete plantilla[i];   // libera cada jugador
    }
}

string Equipo::getNombre() const { return nombrePais; }
string Equipo::getConfederacion() const { return confederacion; }
unsigned short int Equipo::getRanking() const { return rankingFIFA; }
const Estadistica& Equipo::getEstadisticas() const { return estadisticasHist; }

void Equipo::setEstadisticasHistoricas(const Estadistica& stats) { estadisticasHist = stats; }

float Equipo::obtenerPromedioGolesFavor() const {
    unsigned short int partidos = estadisticasHist.getPartidosJugados();
    return (partidos == 0) ? 0.0f : static_cast<float>(estadisticasHist.getGolesFavor()) / partidos;
}

float Equipo::obtenerPromedioGolesContra() const {
    unsigned short int partidos = estadisticasHist.getPartidosJugados();
    return (partidos == 0) ? 0.0f : static_cast<float>(estadisticasHist.getGolesContra()) / partidos;
}

Lista<Jugador*> Equipo::obtenerGoleadores() const {
    Lista<Jugador*> goleadores;
    for (int i = 0; i < plantilla.obtenerTamanio(); ++i) {
        Jugador* j = plantilla[i];   // ya es puntero
        if (j->getGoles() > 0) {
            goleadores.agregar(j);
        }
    }
    return goleadores;
}


void Equipo::agregarJugador(Jugador* j) {
    if (j) {
        plantilla.agregar(j);   // almacena el puntero
    }
}

unsigned short int Equipo::obtenerJugadores(Jugador* destino[], unsigned short int max) const {
    unsigned short int total = plantilla.obtenerTamanio();
    unsigned short int copiar = (total < max) ? total : max;
    for (unsigned short int i = 0; i < copiar; ++i) {
        destino[i] = plantilla[i];   // plantilla[i] ya es Jugador*
    }
    return copiar;
}

Jugador* Equipo::obtenerJugadorPorNumero(unsigned short int numero) const {
    for (int i = 0; i < plantilla.obtenerTamanio(); ++i) {
        Jugador* j = plantilla[i];
        if (j && j->getNumeroCamiseta() == numero) {
            return j;
        }
    }
    return nullptr;
}

Jugador* Equipo::obtenerJugadorPorIndice(unsigned short int indice) const {
    if (indice >= plantilla.obtenerTamanio()) return nullptr;
    return plantilla[indice];
}

void Equipo::actualizarEstadisticas(const Estadistica& statsPartido) {
    estadisticasHist.actualizar(statsPartido);
}

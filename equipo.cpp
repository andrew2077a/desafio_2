#include "Equipo.h"

// Constructor por defecto
Equipo::Equipo()
    : nombrePais(""), confederacion(""), rankingFIFA(0), directorTecnico("") {}

// Constructor con parametros
Equipo::Equipo(const std::string& nombre, const std::string& conf,
               unsigned short int ranking, const std::string& dt)
    : nombrePais(nombre), confederacion(conf),
    rankingFIFA(ranking), directorTecnico(dt) {}

// Destructor: libera jugadores
Equipo::~Equipo()
{
    for (int i = 0; i < plantilla.obtenerTamanio(); ++i) {
        delete plantilla[i];
    }
}

// Getters
std::string Equipo::getNombre() const { return nombrePais; }
unsigned short int Equipo::getRanking() const { return rankingFIFA; }
const Estadistica& Equipo::getEstadisticas() const { return estadisticasHist; }

float Equipo::obtenerPromedioGolesFavor() const
{
    unsigned short int partidos = estadisticasHist.getPartidosJugados();
    if (partidos == 0) return 0.0f;
    return static_cast<float>(estadisticasHist.getGolesFavor()) / partidos;
}

float Equipo::obtenerPromedioGolesContra() const
{
    unsigned short int partidos = estadisticasHist.getPartidosJugados();
    if (partidos == 0) return 0.0f;
    return static_cast<float>(estadisticasHist.getGolesContra()) / partidos;
}

Lista<Jugador*> Equipo::obtenerGoleadores() const
{
    Lista<Jugador*> goleadores;
    for (int i = 0; i < plantilla.obtenerTamanio(); ++i) {
        Jugador* j = plantilla[i];
        if (j->getGoles() > 0) {
            goleadores.agregar(j);
        }
    }
    return goleadores;
}

void Equipo::agregarJugador(Jugador* j)
{
    if (j != nullptr) {
        plantilla.agregar(j);
    }
}

void Equipo::actualizarEstadisticas(const Estadistica& statsPartido)
{
    estadisticasHist.actualizar(statsPartido);
}

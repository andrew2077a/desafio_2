#include "Equipo.h"
#include "Partido.h"

Equipo::Equipo() : nombrePais(""), confederacion(""), rankingFIFA(0), directorTecnico("") {
}

Equipo::Equipo(string nombre, string conf, unsigned short int ranking, string dt)
    : nombrePais(nombre),
    confederacion(conf),
    rankingFIFA(ranking),
    directorTecnico(dt) {}
Equipo::~Equipo() {
}

float Equipo::obtenerPromedioGolesFavor() const {
    unsigned short int partidos = estadisticasHist.getPartidosJugados();
    if (partidos == 0) return 0.0f;
    return (float)estadisticasHist.getGolesFavor() / partidos;
}

float Equipo::obtenerPromedioGolesContra() const {
    int partidos = estadisticasHist.getPartidosJugados();
    if (partidos == 0) return 0.0f;
    return (float)estadisticasHist.getGolesContra() / partidos;
}

Lista<Jugador*> Equipo::obtenerGoleadores() const {
    Lista<Jugador*> goleadores;
    for (int i = 0; i < plantilla.obtenerTamanio(); ++i) {
        Jugador* j = plantilla[i];
        if (j->getGoles() > 0) {
            goleadores.agregar(j);
        }
    }
    return goleadores; // El compilador optimiza esto (RVO)
}

void Equipo::agregarJugador(Jugador* j) {
    if (j != nullptr) {
        plantilla.agregar(j); // Usamos '.'
    }
}

string Equipo::getNombre() const { return nombrePais; }
int Equipo::getRanking() const { return (int)rankingFIFA; }

void Equipo::actualizarEstadisticas(Partido* partido) {
    if (partido == nullptr) return;

    unsigned short int golesF = 0;
    unsigned short int golesC = 0;

    // 1. Determinar el rol del equipo comparando direcciones de memoria (this)
    if (partido->getEquipoLocal() == this) {
        golesF = (unsigned short int)partido->getGolesLocal();
        golesC = (unsigned short int)partido->getGolesVisitante();
    }
    else if (partido->getEquipoVisitante() == this) {
        golesF = (unsigned short int)partido->getGolesVisitante();
        golesC = (unsigned short int)partido->getGolesLocal();
    } else {
        return; // El equipo no participó en este partido
    }

    // 2. Determinar resultado para el historial
    unsigned short int pg = (golesF > golesC) ? 1 : 0;
    unsigned short int pe = (golesF == golesC) ? 1 : 0;
    unsigned short int pp = (golesF < golesC) ? 1 : 0;

    // 3. Crear objeto temporal con los datos del partido
    // Orden: gF, gC, PG, PE, PP, TA, TR, Faltas, Min, Asist
    Estadistica infoPartido(golesF, golesC, pg, pe, pp, 0, 0, 0, 0, 0);

    // 4. Sumar al historial acumulado usando tu método actualizar
    this->estadisticasHist.actualizar(infoPartido);
}

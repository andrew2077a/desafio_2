#include "Equipo.h"
#include "Partido.h"

// Constructor por defecto
Equipo::Equipo() : nombrePais(""), confederacion(""), rankingFIFA(0), directorTecnico("") {
    plantilla = new Lista<Jugador*>();
}

// Constructor por valor
Equipo::Equipo(string nombre, string conf, int ranking, string dt) {
    nombrePais = nombre;
    confederacion = conf;
    rankingFIFA = ranking;
    directorTecnico = dt;
    plantilla = new Lista<Jugador*>();
}

// Destructor
Equipo::~Equipo() {
    if (plantilla != nullptr) {
        delete plantilla;
    }
}

float Equipo::obtenerPromedioGolesFavor() const {
    int partidos = estadisticasHist.getPartidosJugados();
    if (partidos == 0) return 0.0f;
    return (float)estadisticasHist.getGolesFavor() / partidos;
}

float Equipo::obtenerPromedioGolesContra() const {
    int partidos = estadisticasHist.getPartidosJugados();
    if (partidos == 0) return 0.0f;
    return (float)estadisticasHist.getGolesContra() / partidos;
}

Lista<Jugador*>* Equipo::obtenerGoleadores() {
    Lista<Jugador*>* goleadores = new Lista<Jugador*>();
    for (int i = 0; i < plantilla->obtenerTamanio(); i++) {
        Jugador* j = (*plantilla)[i];
        // Aquí asumo que Jugador también tiene un objeto Estadistica dentro
        if (j->getGoles() > 0) {
            goleadores->agregar(j);
        }
    }
    return goleadores;
}

void Equipo::agregarJugador(Jugador* j) {
    if (j != nullptr) {
        plantilla->agregar(j);
    }
}

string Equipo::getNombre() const { return nombrePais; }
int Equipo::getRanking() const { return rankingFIFA; }

void Equipo::actualizarEstadisticas(Partido* partido) {
    // Lógica pendiente de la implementación de Partido
}

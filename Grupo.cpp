#include "Grupo.h"
#include "Equipo.h"
#include <iostream>
#include <cstdlib>
#include "Fecha.h"
using namespace std;

static int mi_abs(int x){
    return (x < 0) ? -x : x;
}

static int diasAbsolutos(const Fecha& fecha) {
    return fecha.getDia() + fecha.getMes() * 30 + fecha.getAnio() * 360;
}

static bool fechaValida(const Fecha& fecha, const Fecha* fechasPrevias,
                        unsigned short int numPrevias, int diasMinimos) {
    int fechaAbs = diasAbsolutos(fecha);
    for (unsigned short int i = 0; i < numPrevias; ++i) {
        int prevAbs = diasAbsolutos(fechasPrevias[i]);
        if (mi_abs(fechaAbs - prevAbs) < diasMinimos)
            return false;
    }
    return true;
}

void Grupo::setLetra(char l) { letra = l; }

// Constructor
Grupo::Grupo() : letra('?'), numEquipos(0) {
    for (int i = 0; i < 4; ++i) equipos[i] = nullptr;
}

// Destructor (no elimina equipos, solo los olvida)
Grupo::~Grupo() {}


// Métodos para gestión de equipos
bool Grupo::agregarEquipo(Equipo* equipo) {
    if (!equipo) return false;
    if (numEquipos >= 4) return false;
    if (!puedeAgregar(equipo)) return false;

    equipos[numEquipos++] = equipo;
    return true;
}

bool Grupo::puedeAgregar(Equipo* equipo) const {
    if (!equipo) return false;

    // Contar cuantos equipos de la misma confederacion ya están en el grupo
    int uefaCount = 0;
    for (int i = 0; i < numEquipos; ++i) {
        if (equipos[i]->getConfederacion() == equipo->getConfederacion()) {
            // Si es UEFA, se permite max.2
            if (equipo->getConfederacion() == "UEFA") {
                uefaCount++;
                if (uefaCount >= 2) return false;
            } else {
                return false;   // ya hay un equipo de esta confederación no-UEFA
            }
        }
    }
    return true;
}

void Grupo::agregarEquipoForzado(Equipo* equipo) {
    if (!equipo || numEquipos >= 4) return;
    equipos[numEquipos++] = equipo;
}

void Grupo::imprimirGrupo() const {
    cout << "Grupo " << letra << ": ";
    for (int i = 0; i < numEquipos; ++i) {
        if (equipos[i])
            cout << equipos[i]->getNombre() << " ";
    }
    cout << endl;
}

// Fixture y simulación (implementaciones previas)
void Grupo::generarFixture(const Fecha& fechaInicio) {
    const int partidosIndices[6][2] = {
        {0,1}, {0,2}, {0,3}, {1,2}, {1,3}, {2,3}
    };

    Fecha fechasEquipo[4][3];
    unsigned short int numPartidosEquipo[4] = {0,0,0,0};

    Fecha fechaActual = fechaInicio;
    const unsigned short int DIAS_MINIMOS = 3;

    for (int i = 0; i < 6; ++i) {
        unsigned short int i1 = partidosIndices[i][0];
        unsigned short int i2 = partidosIndices[i][1];
        Equipo* eq1 = equipos[i1];
        Equipo* eq2 = equipos[i2];
        if (!eq1 || !eq2) continue;

        Fecha fechaPropuesta = fechaActual;
        bool encontrado = false;
        for (int intento = 0; intento < 100 && !encontrado; ++intento) {
            bool ok1 = fechaValida(fechaPropuesta, fechasEquipo[i1], numPartidosEquipo[i1], DIAS_MINIMOS);
            bool ok2 = fechaValida(fechaPropuesta, fechasEquipo[i2], numPartidosEquipo[i2], DIAS_MINIMOS);
            if (ok1 && ok2) {
                encontrado = true;
            } else {
                fechaPropuesta = fechaPropuesta.sumarDias(1);
            }
        }
        if (!encontrado) {
            fechaPropuesta = fechaActual.sumarDias(10); // fallback
        }

        // Crear partido (asumiendo constructor con los parametros adecuados)
        partidos[i] = Partido(fechaPropuesta, "00:00", "nombreSede", eq1, eq2);

        fechasEquipo[i1][numPartidosEquipo[i1]++] = fechaPropuesta;
        fechasEquipo[i2][numPartidosEquipo[i2]++] = fechaPropuesta;

        fechaActual = fechaPropuesta.sumarDias(1);
    }
}



void Grupo::jugarPartidos() {
    for (int i = 0; i < 6; ++i) {
        partidos[i].simular(false);
        partidos[i].actualizarHistoricos();
    }
}

bool Grupo::compararEquipos(const Equipo* a, const Equipo* b) {
    const Estadistica& sa = a->getEstadisticas();
    const Estadistica& sb = b->getEstadisticas();

    int puntosA = sa.getPartidosGanados() * 3 + sa.getPartidosEmpatados();
    int puntosB = sb.getPartidosGanados() * 3 + sb.getPartidosEmpatados();
    if (puntosA != puntosB) return puntosA > puntosB;

    int dgA = sa.diferenciaGoles();
    int dgB = sb.diferenciaGoles();
    if (dgA != dgB) return dgA > dgB;

    int gfA = sa.getGolesFavor();
    int gfB = sb.getGolesFavor();
    if (gfA != gfB) return gfA > gfB;

    return a->getRanking() < b->getRanking(); // criterio determinista
}


void Grupo::ordenarEquipos(Equipo* arr[4]) const {
    // Burbuja para 4 elementos usando compararEquipos estático
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            if (compararEquipos(arr[j+1], arr[j])) {
                Equipo* temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


// Posiciones (implementaciones previas)
void Grupo::obtenerTablaPosiciones(Equipo* (&ordenados)[4]) const {
    for (int i = 0; i < 4; ++i)
        ordenados[i] = equipos[i];
    // Ordenar la copia (burbuja)
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i; ++j) {
            if (!compararEquipos(ordenados[j], ordenados[j+1])) {
                Equipo* tmp = ordenados[j];
                ordenados[j] = ordenados[j+1];
                ordenados[j+1] = tmp;
            }
        }
    }
}


Equipo* Grupo::obtenerTercerPuesto() const {
    Equipo* ordenados[4];
    obtenerTablaPosiciones(ordenados);
    return ordenados[2];
}



// Accesos
Equipo* Grupo::getEquipo(int indice) const {
    if (indice >= 0 && indice < numEquipos) return equipos[indice];
    return nullptr;
}

int Grupo::getNumEquipos() const {
    return numEquipos;
}

Grupo::Grupo(char l) : letra(l), numEquipos(0) {
    for (int i = 0; i < 4; ++i) equipos[i] = nullptr;
}

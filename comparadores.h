#ifndef COMPARADORES_H
#define COMPARADORES_H

#include "Equipo.h"

inline bool esMejorEquipo(const Equipo* a, const Equipo* b) {
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
    return a < b;  // criterio determinista
}

#endif

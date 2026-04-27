#ifndef TORNEO_H
#define TORNEO_H

#include "Equipo.h"
#include "Grupo.h"
#include "Partido.h"
#include "Fecha.h"

class Torneo {
private:
    Equipo** equipos;  // arreglo dinamico de punteros a Equipo
    unsigned short int totalEquipos;
    unsigned short int totalGrupos; // totalEquipos / 4

    Grupo* grupos; // arreglo dinamico de grupos

    // Partidos eliminatorios (punteros, se crean dinamicamente)
    Partido** ronda16;
    Partido** ronda8;
    Partido** cuartos;
    Partido** semis;
    Partido* final;
    Partido* tercerLugar;

    unsigned short int numRonda16;
    unsigned short int numRonda8;
    unsigned short int numCuartos;
    unsigned short int numSemis;

    // Metodos privados auxiliares
    void cargarEquiposDesdeCSV(const std::string& nombreArchivo);
    void cargarJugadoresParaEquipo(Equipo* equipo, unsigned short int numJugadores);
    void asignarGolesIniciales(unsigned short int golesEquipo, Equipo* equipo);

    void ordenarEquipos(Equipo** arr, unsigned short int n);
    void simularRonda(Partido** partidos, unsigned short int numPartidos, bool esEliminatoria);

    void obtenerClasificados(Equipo** &primeros, Equipo** &segundos, Equipo** &terceros,
                             unsigned short int &numPrimeros, unsigned short int &numSegundos,
                             unsigned short int &numTerceros);
    void seleccionarMejoresTerceros(Equipo** terceros, unsigned short int numTerceros,
                                    Equipo** &mejores, unsigned short int &numMejores);
    void construirEmparejamientos(Equipo** clasificados, unsigned short int numClasificados,
                                  Partido** &partidos, unsigned short int &numPartidos);

    void armarGrupos();

    // Prohibir copia
    Torneo(const Torneo&);
    Torneo& operator=(const Torneo&);

public:
    Torneo(const std::string& archivoEquipos);
    ~Torneo();

    void ejecutar();
    void simularFaseGrupos();
    void transicionADieciseisavos();
    void simularEliminatorias();
    void generarInformeFinal();
};

#endif

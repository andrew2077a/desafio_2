#ifndef PARTIDO_H
#define PARTIDO_H

#include <string>
#include "Fecha.h"
#include "Equipo.h"
#include "Estadistica.h"
#include "Lista.h"      // Para usar Lista<Jugador*> si se necesita, pero aquí no se usa directamente

class Partido {
private:
    //Datos fijos
    Fecha fecha;
    std::string hora;
    std::string sede;
    Equipo* equipoLocal;
    Equipo* equipoVisitante;
    std::string arbitros[3];

    // Resultados
    unsigned short int golesLocal;
    unsigned short int golesVisitante;
    float posesionLocal;
    bool prorroga;
    unsigned short int minutosPartido; // 90 o 120

    // Convocados (números de camiseta)
    unsigned short int convocadosLocal[11];
    unsigned short int convocadosVisitante[11];

    // Goleadores (números de camiseta)
    unsigned short int goleadoresLocal[11];
    unsigned short int goleadoresVisitante[11];

    // Contadores
    unsigned short int numGoleadoresLocal;
    unsigned short int numGoleadoresVisitante;

    // Estadísticas del partido que se acumulan por equipo (para luego actualizar)
    Estadistica statsLocalPartido;
    Estadistica statsVisitPartido;

    // Métodos privados de simulación
    void seleccionarConvocados();
    void calcularPosesion();
    float calcularGolesEsperados(Equipo* atacante, Equipo* defensor) const;
    void asignarGoles(Equipo* equipo, float lambda,
                      const unsigned short int* convocados,
                      unsigned short int* goleadores,
                      unsigned short int& numGoleadores,
                      Estadistica& statsEquipo);
    void aplicarTarjetasYFaltas(Equipo* equipo, int* convocados, Estadistica& statsEquipo);
    void aplicarTarjetasYFaltasAJugador(Jugador* jug, Estadistica& statsEquipo);

public:
    // Constructor
    Partido(const Fecha& fecha, const std::string& hora, const std::string& sede,
            Equipo* local, Equipo* visitante);

    // Destructor (no gestiona memoria de equipos ni jugadores)
    ~Partido();

    // Simulación completa
    void simular(bool esEliminatoria = false);   // true => si hay empate, prórroga y desempate por ranking
    void actualizarHistoricos();

    // Getters
    Equipo* getEquipoLocal() const;
    Equipo* getEquipoVisitante() const;
    unsigned short int getGolesLocal() const;
    unsigned short int getGolesVisitante() const;
    float getPosesionLocal() const;
    bool hayProrroga() const;

    // Impresión de resultados (según requisito)
    void imprimirResumen() const;
};

#endif

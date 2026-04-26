#ifndef ESTADISTICA_H
#define ESTADISTICA_H

#include <iostream>

class Estadistica
{
private:
    unsigned short int golesFavor;
    unsigned short int golesContra;
    unsigned short int partidosGanados;
    unsigned short int partidosEmpatados;
    unsigned short int partidosPerdidos;
    unsigned short int tarjetasAmarillas;
    unsigned short int tarjetasRojas;
    unsigned short int faltas;
    unsigned short int minutosJugados;
    unsigned short int asistencias;

public:
    // Constructores
    Estadistica();
    Estadistica(unsigned short int gFavor, unsigned short int gContra,
                unsigned short int ganados, unsigned short int empatados,
                unsigned short int perdidos, unsigned short int amarillas,
                unsigned short int rojas, unsigned short int faltasPartido,
                unsigned short int minutos, unsigned short int asistenciasPartido);
    Estadistica(const Estadistica& otras);

    // Destructor
    ~Estadistica();

    // Operador de asignacion
    Estadistica& operator=(const Estadistica& otras);

    // Getters
    unsigned short int getGolesFavor() const;
    unsigned short int getGolesContra() const;
    unsigned short int getPartidosGanados() const;
    unsigned short int getPartidosEmpatados() const;
    unsigned short int getPartidosPerdidos() const;
    unsigned short int getTarjetasAmarillas() const;
    unsigned short int getTarjetasRojas() const;
    unsigned short int getFaltas() const;
    unsigned short int getMinutosJugados() const;
    unsigned short int getAsistencias() const;
    unsigned short int getPartidosJugados() const;

    // Metodos
    void actualizar(const Estadistica& otras);
    int diferenciaGoles() const;

    // Sobrecarga de operadores
    Estadistica& operator+=(const Estadistica& otras);
    Estadistica operator+(const Estadistica& otras) const;

    // Operador de flujo
    friend std::ostream& operator<<(std::ostream& os, const Estadistica& stats);
};

#endif

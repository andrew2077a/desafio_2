#ifndef ESTADISTICA_H
#define ESTADISTICA_H

class Estadistica{
private:
    int golesFavor;
    int golesContra;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;
    int minutosJuagados;
    int asistencias;

public:
    Estadistica();
    void actualizar(const Estadistica& otras);

    void operator+=(const Estadistica& otras);
    int diferenciaGoles();
};

#endif // ESTADISTICA_H

#include "Estadistica.h"
using namespace std;

// Constructor por defecto
Estadistica::Estadistica()
    : golesFavor(0), golesContra(0), partidosGanados(0),
    partidosEmpatados(0), partidosPerdidos(0), tarjetasAmarillas(0),
    tarjetasRojas(0), faltas(0), minutosJugados(0), asistencias(0) {}

// Constructor con parametros
Estadistica::Estadistica(unsigned short int gFavor, unsigned short int gContra,
                         unsigned short int ganados, unsigned short int empatados,
                         unsigned short int perdidos, unsigned short int amarillas,
                         unsigned short int rojas, unsigned short int faltasPartido,
                         unsigned short int minutos, unsigned short int asistenciasPartido)
    : golesFavor(gFavor), golesContra(gContra), partidosGanados(ganados),
    partidosEmpatados(empatados), partidosPerdidos(perdidos),
    tarjetasAmarillas(amarillas), tarjetasRojas(rojas), faltas(faltasPartido),
    minutosJugados(minutos), asistencias(asistenciasPartido) {}

// Constructor de copia
Estadistica::Estadistica(const Estadistica& otras)
    : golesFavor(otras.golesFavor), golesContra(otras.golesContra),
    partidosGanados(otras.partidosGanados), partidosEmpatados(otras.partidosEmpatados),
    partidosPerdidos(otras.partidosPerdidos), tarjetasAmarillas(otras.tarjetasAmarillas),
    tarjetasRojas(otras.tarjetasRojas), faltas(otras.faltas),
    minutosJugados(otras.minutosJugados), asistencias(otras.asistencias) {}

// Destructor
Estadistica::~Estadistica() {}

// Operador de asignacion
Estadistica& Estadistica::operator=(const Estadistica& otras)
{
    if (this == &otras) return *this;
    golesFavor = otras.golesFavor;
    golesContra = otras.golesContra;
    partidosGanados = otras.partidosGanados;
    partidosEmpatados = otras.partidosEmpatados;
    partidosPerdidos = otras.partidosPerdidos;
    tarjetasAmarillas = otras.tarjetasAmarillas;
    tarjetasRojas = otras.tarjetasRojas;
    faltas = otras.faltas;
    minutosJugados = otras.minutosJugados;
    asistencias = otras.asistencias;
    return *this;
}

// Getters
unsigned short int Estadistica::getGolesFavor() const { return golesFavor; }
unsigned short int Estadistica::getGolesContra() const { return golesContra; }
unsigned short int Estadistica::getPartidosGanados() const { return partidosGanados; }
unsigned short int Estadistica::getPartidosEmpatados() const { return partidosEmpatados; }
unsigned short int Estadistica::getPartidosPerdidos() const { return partidosPerdidos; }
unsigned short int Estadistica::getTarjetasAmarillas() const { return tarjetasAmarillas; }
unsigned short int Estadistica::getTarjetasRojas() const { return tarjetasRojas; }
unsigned short int Estadistica::getFaltas() const { return faltas; }
unsigned short int Estadistica::getMinutosJugados() const { return minutosJugados; }
unsigned short int Estadistica::getAsistencias() const { return asistencias; }
unsigned short int Estadistica::getPartidosJugados() const {
    return partidosGanados + partidosEmpatados + partidosPerdidos;
}

// Metodos
void Estadistica::actualizar(const Estadistica& otras)
{
    golesFavor += otras.golesFavor;
    golesContra += otras.golesContra;
    partidosGanados += otras.partidosGanados;
    partidosEmpatados += otras.partidosEmpatados;
    partidosPerdidos += otras.partidosPerdidos;
    tarjetasAmarillas += otras.tarjetasAmarillas;
    tarjetasRojas += otras.tarjetasRojas;
    faltas += otras.faltas;
    minutosJugados += otras.minutosJugados;
    asistencias += otras.asistencias;
}

int Estadistica::diferenciaGoles() const
{
    return static_cast<int>(golesFavor) - static_cast<int>(golesContra);
}

// Sobrecarga de operadores
Estadistica& Estadistica::operator+=(const Estadistica& otras)
{
    actualizar(otras);
    return *this;
}

Estadistica Estadistica::operator+(const Estadistica& otras) const
{
    Estadistica resultado(*this);
    resultado += otras;
    return resultado;
}

// Operador de flujo
ostream& operator<<(ostream& os, const Estadistica& stats)
{
    os << "Goles F: " << stats.golesFavor
       << " | Goles C: " << stats.golesContra
       << " | PG: " << stats.partidosGanados
       << " | PE: " << stats.partidosEmpatados
       << " | PP: " << stats.partidosPerdidos
       << " | TA: " << stats.tarjetasAmarillas
       << " | TR: " << stats.tarjetasRojas
       << " | Faltas: " << stats.faltas
       << " | Min: " << stats.minutosJugados
       << " | Asist: " << stats.asistencias;
    return os;
}

#ifndef PARTIDO_H
#define PARTIDO_H

class Partido{
private:
    Fecha fecha;
    string hora;
    string sede;
    equipo* equipoLocal;
    equipo* golesVisitante;
    int golesLocal;
    int golesVisitante;
    bool prorroga;
    float posesionLocal;
    string arbitros[3];
    ListaInt*  convocadosLocal;
    ListaInt*  convocadosVisitante;

public:
    Partido();
    void sumar();
    actualizarHistoricos();
    ListaInt* obtenerGoleadoresPartido();


};

#endif // PARTIDO_H

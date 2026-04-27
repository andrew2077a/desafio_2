#ifndef GRUPO_H
#define GRUPO_H
#include "Equipo.h"
#include "Partido.h"
#include "Fecha.h"

class Grupo {
private:
    char letra;
    Equipo* equipos[4];
    Partido partidos[6];
    unsigned short int numEquipos;

    // Prohibir copia (mantener privado)
    Grupo(const Grupo&);
    Grupo& operator=(const Grupo&);

    static bool compararEquipos(const Equipo* a, const Equipo* b); // comparador estático
    void ordenarEquipos(Equipo* arr[4]) const;   // ordena un array de 4 punteros

public:
    Grupo();   // constructor por defecto (público)
    Grupo(char letra);
    ~Grupo();

    void setLetra(char l);   // método público

    // Resto de métodos...
    bool agregarEquipo(Equipo* equipo);
    bool puedeAgregar(Equipo* equipo) const;
    void imprimirGrupo() const;

    void generarFixture(const Fecha& fechaInicio);
    void jugarPartidos();

    void obtenerTablaPosiciones(Equipo* (&ordenados)[4]) const;   // ahora ordena una copia
    Equipo* obtenerTercerPuesto() const;

    Equipo* getEquipo(int indice) const;
    int getNumEquipos() const;
};

#endif

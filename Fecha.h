#ifndef FECHA_H
#define FECHA_H

#include <iostream>
using namespace std;

class Fecha
{
private:
    unsigned short int dia;
    unsigned short int mes;
    unsigned short int anio;

public:
    // Constructores
    Fecha(); //--> predeterminado
    Fecha(int dia_x, int mes_x, int anio_x); //---> por valor
    Fecha(const Fecha& otra); //---> constructor de copia

    // Destructor
    ~Fecha();

    // getters
    unsigned short int get_dia() const;
    unsigned short int get_mes() const;
    unsigned short int get_anio() const;

    // setters
    void set_dia(unsigned short int dato);
    void set_mes(unsigned short int dato);
    void set_anio(unsigned short int dato);

    // sobrecarga de operadores
    bool operator==(const Fecha& otra) const;
    bool operator<(const Fecha& otra) const;
    bool operator>(const Fecha& otra) const;
    bool operator<=(const Fecha& otra) const;
    bool operator>=(const Fecha& otra) const;

    // metodo auxiliar de suma
    Fecha sumarDias(unsigned short int dias_extra) const;

    // operador de flujo --->cout (uso de friend para evitar usar getters)
    friend ostream& operator<<(ostream& os, const Fecha& fecha);
};

#endif

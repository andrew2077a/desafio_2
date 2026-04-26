#ifndef FECHA_H
#define FECHA_H

#include <iostream>

class Fecha
{
private:
    unsigned short int dia;
    unsigned short int mes;
    unsigned short int anio;

public:
    // Constructores
    Fecha();  // Por defecto
    Fecha(int dia_x, int mes_x, int anio_x); // Con parametros
    Fecha(const Fecha& otra); // Copia

    // Destructor
    ~Fecha();

    // Operador de asignación
    Fecha& operator=(const Fecha& otra);

    // Getters
    unsigned short int getDia() const;
    unsigned short int getMes() const;
    unsigned short int getAnio() const;

    // Setters
    void setDia(unsigned short int dato);
    void setMes(unsigned short int dato);
    void setAnio(unsigned short int dato);

    // Sobrecarga de operadores
    bool operator==(const Fecha& otra) const;
    bool operator<(const Fecha& otra) const;
    bool operator>(const Fecha& otra) const;
    bool operator<=(const Fecha& otra) const;
    bool operator>=(const Fecha& otra) const;

    // Metodo auxiliar
    Fecha sumarDias(unsigned short int dias_extra) const;

    // Operador de flujo
    friend std::ostream& operator<<(std::ostream& os, const Fecha& fecha);
};

#endif

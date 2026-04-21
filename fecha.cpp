#include "fecha.h"

// Constructor
Fecha::Fecha(int dia_x, int mes_x, int anio_x)
{
    bool check_dia = (dia_x >= 1 && dia_x <= 30);
    bool check_mes = (mes_x >= 1 && mes_x <= 12);
    bool check_anio = (anio_x >= 2026);

    if (check_dia && check_mes && check_anio) {
        dia = dia_x;
        mes = mes_x;
        anio = anio_x;
    } else {
        dia = 1;
        mes = 1;
        anio = 2026;
    }
}

// Getters
unsigned short int Fecha::get_dia() const
{
    return dia;
}

unsigned short int Fecha::get_mes() const
{
    return mes;
}

unsigned short int Fecha::get_anio() const
{
    return anio;
}

// Setters
void Fecha::set_dia(unsigned short int dato)
{
    if (dato >= 1 && dato <= 30) {
        dia = dato;
    }
}

void Fecha::set_mes(unsigned short int dato)
{
    if (dato >= 1 && dato <= 12) {
        mes = dato;
    }
}

void Fecha::set_anio(unsigned short int dato)
{
    if (dato >= 2026) {
        anio = dato;
    }
}

// Operador ==
bool Fecha::operator==(const Fecha& otra) const
{
    return (dia == otra.dia &&
            mes == otra.mes &&
            anio == otra.anio);
}

// Operador <
bool Fecha::operator<(const Fecha& otra) const
{
    if (anio != otra.anio) {
        return anio < otra.anio;
    }
    if (mes != otra.mes) {
        return mes < otra.mes;
    }
    return dia < otra.dia;
}

// Operador >
bool Fecha::operator>(const Fecha& otra) const
{
    return !(*this < otra) && !(*this == otra);
}

// Operador <=
bool Fecha::operator<=(const Fecha& otra) const
{
    return (*this < otra) || (*this == otra);
}

// Operador >=
bool Fecha::operator>=(const Fecha& otra) const
{
    return !(*this < otra);
}

// Sumar días
Fecha Fecha::sumarDias(unsigned short int dias_extra) const
{
    Fecha nuevo(dia, mes, anio);

    nuevo.dia += dias_extra;

    while (nuevo.dia > 30) {
        nuevo.dia -= 30;
        nuevo.mes += 1;

        if (nuevo.mes > 12) {
            nuevo.mes = 1;
            nuevo.anio += 1;
        }
    }

    return nuevo;
}

ostream& operator<<(ostream& os, const Fecha& fecha)
{
    os << fecha.dia << "/" << fecha.mes << "/" << fecha.anio;
    return os;
}

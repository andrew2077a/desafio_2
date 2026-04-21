#ifndef FECHA_H
#define FECHA_H

class Fecha{
private:
    int dia;
    int mes;
    int anio;

public:
    Fecha(int d, int m , int a);
    bool operator==(Fecha otra);
    bool operator<(Fecha otra);
    Fecha sumarDias(int dias);
};

#endif // FECHA_H

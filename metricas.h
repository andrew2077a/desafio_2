#ifndef METRICAS_H
#define METRICAS_H

#include <string>
#include <iostream>

using namespace std;

class Metricas {
private:
    // Variables estáticas (compartidas por toda la aplicación)
    static unsigned long long contadorIteraciones;
    static unsigned long long memoriaBytes;

public:
    // ===== GESTIÓN DE ITERACIONES =====

    static void resetearIteraciones();

    static void contarIteracion(unsigned long long cantidad = 1);

    static unsigned long long getIteraciones();

    static void resetearMemoria();

    static void registrarMemoria(unsigned long long bytes);

    static unsigned long long getMemoria();

    static void resetearTodo();

    static void rehacer_memoria();

    static void mostrarReporte(const string& nombreFuncionalidad);

};

#endif // METRICAS_H

#include "Metricas.h"
#include <iomanip>

// Inicialización de variables estáticas (OBLIGATORIO en C++)
unsigned long long Metricas::contadorIteraciones = 0;
unsigned long long Metricas::memoriaBytes = 0;

// ===== GESTIÓN DE ITERACIONES =====

void Metricas::resetearIteraciones() {
    contadorIteraciones = 0;
}

void Metricas::contarIteracion(unsigned long long cantidad) {
    contadorIteraciones += cantidad;
}

unsigned long long Metricas::getIteraciones() {
    return contadorIteraciones;
}

// ===== GESTIÓN DE MEMORIA =====

void Metricas::resetearMemoria() {
    memoriaBytes = 0;
}

void Metricas::rehacer_memoria(unsigned long long bytes){
    memoriaBytes=bytes;

}

void Metricas::registrarMemoria(unsigned long long bytes) {
    memoriaBytes += bytes;
}

unsigned long long Metricas::getMemoria() {
    return memoriaBytes;
}

// ===== UTILIDADES =====

void Metricas::resetearTodo() {
    resetearIteraciones();
    resetearMemoria();
}


void Metricas::mostrarReporte(const string& nombreFuncionalidad) {
    cout << "\n";
    cout << "_________________________________________\n";
    cout << "  REPORTE DE EFICIENCIA\n";
    cout << "_________________________________________\n";
    cout << "Funcionalidad: " << nombreFuncionalidad << "\n";
    cout << "----------------------------------------\n";

    // Mostrar iteraciones
    cout << "Iteraciones ejecutadas: " << contadorIteraciones << "\n";

    // Mostrar memoria
    cout << "Memoria consumida:      " << memoriaBytes << " bytes";

    cout << "___________________________________________\n\n";
}

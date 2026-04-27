#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Torneo.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "========================================\n";
    cout << "    UdeAWorldCup - Simulador FIFA 2026  \n";
    cout << "========================================\n";

    cout << "Ingrese el nombre del archivo CSV de equipos: ";
    string archivo;
    cin >> archivo;

    // El constructor de Torneo carga equipos y jugadores desde el CSV
    Torneo torneo(archivo);

    int opcion = -1;
    while (opcion != 0) {
        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1. Simular fase de grupos\n";
        cout << "2. Transicion a dieciseisavos\n";
        cout << "3. Simular eliminatorias (R16 -> Final)\n";
        cout << "4. Generar informe final\n";
        cout << "5. Ejecutar torneo completo\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: torneo.simularFaseGrupos();         break;
        case 2: torneo.transicionADieciseisavos();  break;
        case 3: torneo.simularEliminatorias();      break;
        case 4: torneo.generarInformeFinal();       break;
        case 5: torneo.ejecutar();                  break;
        case 0: cout << "Hasta luego!\n";           break;
        default: cout << "Opcion invalida.\n";      break;
        }
    }

    return 0;
}

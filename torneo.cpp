#include "Torneo.h"
#include "Metricas.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;

static bool esMejorEquipoTorneo(const Equipo* a, const Equipo* b) {
    const Estadistica& sa = a->getEstadisticas();
    const Estadistica& sb = b->getEstadisticas();

    int puntosA = sa.getPartidosGanados() * 3 + sa.getPartidosEmpatados();
    int puntosB = sb.getPartidosGanados() * 3 + sb.getPartidosEmpatados();
    if (puntosA != puntosB) return puntosA > puntosB;

    int dgA = sa.diferenciaGoles();
    int dgB = sb.diferenciaGoles();
    if (dgA != dgB) return dgA > dgB;

    int gfA = sa.getGolesFavor();
    int gfB = sb.getGolesFavor();
    if (gfA != gfB) return gfA > gfB;

    return a->getRanking() < b->getRanking(); // criterio determinista
}

// Constructor
Torneo::Torneo(const string& archivoEquipos)
    : equipos(nullptr), totalEquipos(0), totalGrupos(0),
    grupos(nullptr), ronda16(nullptr), ronda8(nullptr), cuartos(nullptr),
    semis(nullptr), final(nullptr), tercerLugar(nullptr),
    numRonda16(0), numRonda8(0), numCuartos(0), numSemis(0)
{
    cargarEquiposDesdeCSV(archivoEquipos);
    // Calcular grupos (4 equipos por grupo)
    totalGrupos = totalEquipos / 4;
    grupos = new Grupo[totalGrupos];
    // Inicializar grupos con letras A, B, C...
    for (unsigned short int i = 0; i < totalGrupos; ++i) {
        grupos[i].setLetra(static_cast<char>('A' + i));
    }
    armarGrupos();
}


// Destructor
Torneo::~Torneo() {
    // Liberar equipos (cada equipo libera sus jugadores)
    for (unsigned short int i = 0; i < totalEquipos; ++i) {
        delete equipos[i];
    }
    delete[] equipos;
    delete[] grupos;

    // Liberar partidos eliminatorios
    if (ronda16) {
        for (unsigned short int i = 0; i < numRonda16; ++i) delete ronda16[i];
        delete[] ronda16;
    }
    if (ronda8) {
        for (unsigned short int i = 0; i < numRonda8; ++i) delete ronda8[i];
        delete[] ronda8;
    }
    if (cuartos) {
        for (unsigned short int i = 0; i < numCuartos; ++i) delete cuartos[i];
        delete[] cuartos;
    }
    if (semis) {
        for (unsigned short int i = 0; i < numSemis; ++i) delete semis[i];
        delete[] semis;
    }
    delete final;
    delete tercerLugar;
}


// Carga de equipos desde CSV <-- generico
void Torneo::cargarEquiposDesdeCSV(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir " << nombreArchivo << endl;
        return;
    }

    // 1ro: contar lineas de datos (sin encabezados)
    string linea;
    unsigned short int contador = 0;
    bool primeraLineaDatos = true;
    while (getline(archivo, linea)) {
        // Saltar lineas vacias o que no empiecen con digito (ranking)
        if (linea.empty()) continue;
        if (primeraLineaDatos && (linea[0] < '0' || linea[0] > '9')) {
            // Es encabezado, continuar
            continue;
        }
        primeraLineaDatos = false;
        if (linea[0] >= '0' && linea[0] <= '9') {
            ++contador;
        }
    }
    totalEquipos = contador;
    if (totalEquipos == 0) return;

    // Crear arreglo de equipos
    equipos = new Equipo*[totalEquipos];

    // Reiniciar lectura desde el principio
    archivo.clear();
    archivo.seekg(0);
    unsigned short int idx = 0;
    bool encabezado = true;
    while (getline(archivo, linea) && idx < totalEquipos) {
        if (linea.empty()) continue;
        if (encabezado && (linea[0] < '0' || linea[0] > '9')) {
            continue;   // saltar encabezados
        }
        encabezado = false;
        if (linea[0] >= '0' && linea[0] <= '9') {
            // Parsear con ';' como separador
            string campos[11]; // suficiente
            unsigned short int pos = 0;
            unsigned short int start = 0;
            unsigned short int cnt = 0;
            while (cnt < 11 && (pos = linea.find(';', start)) != string::npos) {
                campos[cnt] = linea.substr(start, pos - start);
                start = pos + 1;
                ++cnt;
            }
            if (cnt < 11) campos[cnt] = linea.substr(start);

            // campos[0] = ranking, [1] = país, [2] = DT, [3] = federación, [4] = confederación,
            // [5] = golesF, [6] = golesC, [7] = PG, [8] = PE, [9] = PP
            unsigned short int ranking = static_cast<unsigned short>(stoi(campos[0]));
            string pais = campos[1];
            string dt = campos[2];
            string confederacion = campos[4];
            unsigned short int gF = static_cast<unsigned short>(stoi(campos[5]));
            unsigned short int gC = static_cast<unsigned short>(stoi(campos[6]));
            unsigned short int pg = static_cast<unsigned short>(stoi(campos[7]));
            unsigned short int pe = static_cast<unsigned short>(stoi(campos[8]));
            unsigned short int pp = static_cast<unsigned short>(stoi(campos[9]));

            Equipo* eq = new Equipo(pais, confederacion, ranking, dt);
            // Establecer estadisticas historicas
            Estadistica hist(gF, gC, pg, pe, pp, 0, 0, 0, 0, 0);
            eq->setEstadisticasHistoricas(hist);
            equipos[idx] = eq;

            // Crear jugadores artificiales
            const unsigned short int JUG_POR_EQUIPO = 26;
            cargarJugadoresParaEquipo(eq, JUG_POR_EQUIPO);
            // Distribuir goles historicos entre jugadores
            asignarGolesIniciales(gF, eq);

            ++idx;
        }
    }
    archivo.close();
}

// Asignar goles historicos a los jugadores de forma uniforme
void Torneo::asignarGolesIniciales(unsigned short int golesEquipo, Equipo* equipo) {
    if (!equipo || golesEquipo == 0) return;
    unsigned short int numJug = 26;
    unsigned short int golesPorJug = golesEquipo / numJug;
    unsigned short int resto = golesEquipo % numJug;
    for (unsigned short int i = 0; i < numJug; ++i) {
        unsigned short int g = golesPorJug + (i < resto ? 1 : 0);
        if (g > 0) {
            Jugador* jug = equipo->obtenerJugadorPorIndice(i);
            if (jug) {
                Estadistica statsGol(g, 0, 0, 0, 0, 0, 0, 0, 0, 0);
                jug->actualizarEstadisticas(statsGol);
            }
        }
    }
}

void Torneo::cargarJugadoresParaEquipo(Equipo* equipo, unsigned short int numJugadores) {
    for (unsigned short int i = 1; i <= numJugadores; ++i) {
        string nombre = "nombre" + to_string(i);
        string apellido = "apellido" + to_string(i);
        unsigned short int numero = i;
        Jugador* jug = new Jugador(nombre, apellido, numero);
        equipo->agregarJugador(jug);   // guarda el puntero
    }
}


// Ordenacion de equipos (burbuja)
void Torneo::ordenarEquipos(Equipo** arr, unsigned short int n) {
    for (unsigned short int i = 0; i < n-1; ++i) {
        for (unsigned short int j = 0; j < n-i-1; ++j) {
            if (!esMejorEquipoTorneo(arr[j], arr[j+1])) {
                Equipo* tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}


// Conformacion de grupos (bombos y sorteo)
void Torneo::armarGrupos() {
    // Buscar anfitrion
    Equipo* anfitrion = nullptr;
    unsigned short int idxAnf = 0;
    for (unsigned short int i = 0; i < totalEquipos; ++i) {
        if (equipos[i]->getNombre() == "United States") {
            anfitrion = equipos[i];
            idxAnf = i;
            break;
        }
    }
    // Crear lista de resto de equipos
    Equipo** resto = new Equipo*[totalEquipos-1];
    unsigned short int r = 0;
    for (unsigned short int i = 0; i < totalEquipos; ++i) {
        if (i != idxAnf){
            resto[r++] = equipos[i];
        }
    }
    // Ordenar resto por ranking
    for (unsigned short int i = 0; i < totalEquipos-2; ++i) {
        for (unsigned short int j = i+1; j < totalEquipos-1; ++j) {
            if (resto[i]->getRanking() > resto[j]->getRanking()) {
                Equipo* tmp = resto[i];
                resto[i] = resto[j];
                resto[j] = tmp;
            }
        }
    }
    // Crear bombos: cada bombo tiene exactamente totalGrupos (12) equipos
    // Bombo 0: USA + los primeros (totalGrupos-1) del ranking
    // Bombo 1: siguientes totalGrupos
    // Bombo 2: siguientes totalGrupos
    // Bombo 3: los restantes
    unsigned short int numBombos = 4;
    Equipo** bombos[4];
    unsigned short int tamanios[4];
    for (int b = 0; b < 4; ++b) {
        tamanios[b] = totalGrupos;  // 12 equipos por bombo exacto
        bombos[b] = new Equipo*[tamanios[b]];
    }
    // Bombo 0: anfitrion + los (totalGrupos-1) primeros del ranking
    bombos[0][0] = anfitrion;
    for (unsigned short int i = 0; i < (unsigned short int)(totalGrupos - 1); ++i) {
        bombos[0][i + 1] = resto[i];
    }
    // Bombos 1, 2, 3: siguientes bloques de totalGrupos equipos
    unsigned short int base = totalGrupos - 1;  // primer indice del resto ya usado
    for (int b = 1; b < 4; ++b) {
        for (unsigned short int i = 0; i < totalGrupos; ++i) {
            unsigned short int restIdx = base + (b - 1) * totalGrupos + i;
            bombos[b][i] = (restIdx < (unsigned short int)(totalEquipos - 1)) ? resto[restIdx] : nullptr;
        }
    }

    // Sorteo: asignar un equipo de cada bombo a cada grupo, respetando confederaciones
    srand(static_cast<unsigned>(time(nullptr)));
    for (int bombo = 0; bombo < 4; ++bombo) {
        // Copia de disponibles
        Equipo** disponibles = new Equipo*[tamanios[bombo]];
        for (unsigned short int i = 0; i < tamanios[bombo]; ++i){
            disponibles[i] = bombos[bombo][i];
        }
        for (unsigned short int g = 0; g < totalGrupos; ++g){
            bool asignado = false;
            int intentos = 0;
            while (!asignado && intentos < 200) {
                int idx = rand() % tamanios[bombo];
                ++intentos;  // SIEMPRE incrementar antes del continue
                if (disponibles[idx] == nullptr) continue;
                Equipo* elegido = disponibles[idx];
                if (grupos[g].puedeAgregar(elegido)) {
                    grupos[g].agregarEquipo(elegido);
                    disponibles[idx] = nullptr;
                    asignado = true;
                }
            }
            if (!asignado) {
                // 1. Intentar primero con equipos que sí cumplan la restriccion
                for (unsigned short int i = 0; i < tamanios[bombo]; ++i) {
                    if (disponibles[i] && grupos[g].puedeAgregar(disponibles[i])) {
                        grupos[g].agregarEquipo(disponibles[i]);
                        disponibles[i] = nullptr;
                        asignado = true;
                        break;
                    }
                }
                // 2. Si no encontró ninguno válido, forzar el primero disponible
                if (!asignado) {
                    for (unsigned short int i = 0; i < tamanios[bombo]; ++i) {
                        if (disponibles[i]) {
                            grupos[g].agregarEquipoForzado(disponibles[i]);
                            disponibles[i] = nullptr;
                            break;
                        }
                    }
                }
            }
        }
        delete[] disponibles;
    }
    // Liberar memoria de bombos
    for (int b = 0; b < 4; ++b) delete[] bombos[b];
    delete[] resto;

    // Imprimir grupos formados
    for (unsigned short int g = 0; g < totalGrupos; ++g) {
        grupos[g].imprimirGrupo();
    }
}


// Simulacion de fase de grupos
void Torneo::simularFaseGrupos() {
    Fecha fechaInicio(20, 6, 2026);
    cout << "\n=== FASE DE GRUPOS ===" << endl;
    for (unsigned short int g = 0; g < totalGrupos; ++g) {
        grupos[g].generarFixture(fechaInicio);
        grupos[g].jugarPartidos();
    }
    // Imprimir resultados de cada grupo
    for (unsigned short int g = 0; g < totalGrupos; ++g) {
        Equipo* ordenados[4];
        grupos[g].obtenerTablaPosiciones(ordenados);
        cout << "\n--- Grupo " << (char)('A' + g) << " - Tabla de posiciones ---" << endl;
        cout << "Pos | Equipo                | PJ | PG | PE | PP | GF | GC | DG | PTS" << endl;
        for (int i = 0; i < 4; ++i) {
            if (!ordenados[i]) continue;
            const Estadistica& s = ordenados[i]->getEstadisticas();
            int pts = s.getPartidosGanados()*3 + s.getPartidosEmpatados();
            cout << " " << i+1 << "  | " << ordenados[i]->getNombre();
            // padding
            int len = ordenados[i]->getNombre().length();
            for (int sp = len; sp < 22; ++sp) cout << ' ';
            cout << "| " << s.getPartidosJugados()
                 << "  | " << s.getPartidosGanados()
                 << "  | " << s.getPartidosEmpatados()
                 << "  | " << s.getPartidosPerdidos()
                 << "  | " << s.getGolesFavor()
                 << "  | " << s.getGolesContra()
                 << "  | " << s.diferenciaGoles()
                 << "  | " << pts << endl;
        }
    }
    Metricas::mostrarReporte("Fase de Grupos");
}


// Transicion a dieciseisavos <-- generico
void Torneo::transicionADieciseisavos() {
    // Obtener listas de 1ros, 2dos y 3ros de cada grupo
    Equipo** primeros = new Equipo*[totalGrupos];
    Equipo** segundos = new Equipo*[totalGrupos];
    Equipo** terceros = new Equipo*[totalGrupos];

    unsigned short int numTerceros = totalGrupos;
    for (unsigned short int g = 0; g < totalGrupos; ++g) {
        Equipo* ordenados[4];
        grupos[g].obtenerTablaPosiciones(ordenados);
        primeros[g] = ordenados[0];
        segundos[g] = ordenados[1];
        terceros[g] = ordenados[2];
    }

    // Seleccionar mejores terceros (generalmente 8, pero depende del formato)
    unsigned short int numMejoresTerceros = (totalGrupos * 2) / 3;
    Equipo** mejoresTerceros = nullptr;
    seleccionarMejoresTerceros(terceros, numTerceros, mejoresTerceros, numMejoresTerceros);

    // Construir clasificados (primeros + segundos + mejores terceros)
    unsigned short int numClasificados = totalGrupos * 2 + numMejoresTerceros;
    Equipo** clasificados = new Equipo*[numClasificados];

    for (unsigned short int i = 0; i < totalGrupos; ++i){
        clasificados[i] = primeros[i];
    }
    for (unsigned short int i = 0; i < totalGrupos; ++i){
        clasificados[totalGrupos + i] = segundos[i];
    }
    for (unsigned short int i = 0; i < numMejoresTerceros; ++i){
        clasificados[2*totalGrupos + i] = mejoresTerceros[i];
    }

    // Construir emparejamientos de R16
    construirEmparejamientos(clasificados, numClasificados, ronda16, numRonda16);

    // Imprimir partidos configurados para R16 (sin simular)
    cout << "\n=== PARTIDOS CONFIGURADOS PARA DIECISEISAVOS (R16) ===" << endl;
    for (unsigned short int i = 0; i < numRonda16; ++i) {
        if (ronda16[i]) {
            cout << "Partido " << i+1 << ": "
                 << ronda16[i]->getEquipoLocal()->getNombre()
                 << " vs "
                 << ronda16[i]->getEquipoVisitante()->getNombre() << endl;
        }
    }
    Metricas::mostrarReporte("Transicion a Dieciseisavos");
    // Liberar memoria temporal
    delete[] primeros; delete[] segundos; delete[] terceros; delete[] mejoresTerceros; delete[] clasificados;
}

void Torneo::seleccionarMejoresTerceros(Equipo** terceros, unsigned short int numTerceros,
                                        Equipo** &mejores, unsigned short int &numMejores) {
    // Copiar terceros a array temporal
    Equipo** temp = new Equipo*[numTerceros];
    for (unsigned short int i = 0; i < numTerceros; ++i){
        temp[i] = terceros[i];
    }

    ordenarEquipos(temp, numTerceros);
    numMejores = (numTerceros * 2) / 3;

    if (numMejores > numTerceros){
        numMejores = numTerceros;
    }
    mejores = new Equipo*[numMejores];
    for (unsigned short int i = 0; i < numMejores; ++i){
        mejores[i] = temp[i];
    }

    delete[] temp;
}

void Torneo::construirEmparejamientos(Equipo** clasificados, unsigned short int numClasificados,
                                      Partido** &partidos, unsigned short int &numPartidos) {
    numPartidos = numClasificados / 2;
    partidos = new Partido*[numPartidos];
    // Simplemente emparejar orden secuencial (se podria)
    Fecha fechaEmparejamiento(10, 7, 2026);
    for (unsigned short int i = 0; i < numPartidos; ++i) {
        partidos[i] = new Partido(fechaEmparejamiento, "00:00", "nombreSede",
                                  clasificados[2*i], clasificados[2*i+1]);
    }
}


// Simulacion de rondas eliminatorias ---> generica
void Torneo::simularRonda(Partido** partidos, unsigned short int numPartidos, bool esEliminatoria) {
    for (unsigned short int i = 0; i < numPartidos; ++i) {
        if (partidos[i]) {
            partidos[i]->simular(esEliminatoria);
            partidos[i]->actualizarHistoricos();
        }
    }
}

void Torneo::simularEliminatorias() {
    if (!ronda16 || numRonda16 == 0) {
        cout << "Error: primero ejecute transicionADieciseisavos()." << endl;
        return;
    }

    // ---- R16: 16 partidos -> 16 ganadores ----
    cout << "\n=== DIECISEISAVOS DE FINAL (R16) ===" << endl;
    simularRonda(ronda16, numRonda16, true);
    for (unsigned short int i = 0; i < numRonda16; ++i) {
        if (ronda16[i]) ronda16[i]->imprimirResumen();
    }

    Equipo** ganadores16 = new Equipo*[numRonda16];
    for (unsigned short int i = 0; i < numRonda16; ++i) {
        Partido* p = ronda16[i];
        ganadores16[i] = (p->getGolesLocal() >= p->getGolesVisitante())
                             ? p->getEquipoLocal() : p->getEquipoVisitante();
    }

    // ---- R8 (Octavos): 8 partidos -> 8 ganadores ----
    cout << "\n=== OCTAVOS DE FINAL (R8) ===" << endl;
    construirEmparejamientos(ganadores16, numRonda16, ronda8, numRonda8);
    simularRonda(ronda8, numRonda8, true);
    for (unsigned short int i = 0; i < numRonda8; ++i) {
        if (ronda8[i]) ronda8[i]->imprimirResumen();
    }

    Equipo** ganadores8 = new Equipo*[numRonda8];
    for (unsigned short int i = 0; i < numRonda8; ++i) {
        Partido* p = ronda8[i];
        ganadores8[i] = (p->getGolesLocal() >= p->getGolesVisitante())
                            ? p->getEquipoLocal() : p->getEquipoVisitante();
    }

    // ---- Cuartos: 4 partidos -> 4 ganadores ----
    cout << "\n=== CUARTOS DE FINAL ===" << endl;
    construirEmparejamientos(ganadores8, numRonda8, cuartos, numCuartos);
    simularRonda(cuartos, numCuartos, true);
    for (unsigned short int i = 0; i < numCuartos; ++i) {
        if (cuartos[i]) cuartos[i]->imprimirResumen();
    }

    Equipo** ganadores4 = new Equipo*[numCuartos];
    for (unsigned short int i = 0; i < numCuartos; ++i) {
        Partido* p = cuartos[i];
        ganadores4[i] = (p->getGolesLocal() >= p->getGolesVisitante())
                            ? p->getEquipoLocal() : p->getEquipoVisitante();
    }

    // ---- Semis: 2 partidos -> 2 finalistas + 2 para 3er lugar ----
    cout << "\n=== SEMIFINALES ===" << endl;
    construirEmparejamientos(ganadores4, numCuartos, semis, numSemis);
    simularRonda(semis, numSemis, true);
    for (unsigned short int i = 0; i < numSemis; ++i) {
        if (semis[i]) semis[i]->imprimirResumen();
    }

    Equipo* finalistas[2];
    Equipo* perdedores[2];
    for (unsigned short int i = 0; i < numSemis && i < 2; ++i) {
        Partido* p = semis[i];
        if (p->getGolesLocal() >= p->getGolesVisitante()) {
            finalistas[i] = p->getEquipoLocal();
            perdedores[i] = p->getEquipoVisitante();
        } else {
            finalistas[i] = p->getEquipoVisitante();
            perdedores[i] = p->getEquipoLocal();
        }
    }

    // ---- Tercer lugar ----
    cout << "\n=== TERCER LUGAR ===" << endl;
    Fecha fechaFin(10, 7, 2026);
    tercerLugar = new Partido(fechaFin, "00:00", "nombreSede", perdedores[0], perdedores[1]);
    tercerLugar->simular(true);
    tercerLugar->actualizarHistoricos();
    tercerLugar->imprimirResumen();

    // ---- Final ----
    cout << "\n=== FINAL ===" << endl;
    final = new Partido(fechaFin, "00:00", "nombreSede", finalistas[0], finalistas[1]);
    final->simular(true);
    final->actualizarHistoricos();
    final->imprimirResumen();

    delete[] ganadores16;
    delete[] ganadores8;
    delete[] ganadores4;
}


// Informe final (simplificado pero completo)
void Torneo::generarInformeFinal() {
    cout << "\n╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║                 INFORME FINAL DEL MUNDIAL 2026                ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

    // ========================== 1. RANKING DE LOS 4 PRIMEROS PUESTOS ==========================
    cout << "1. RANKING DE LOS 4 PRIMEROS PUESTOS:"<<endl;
    if (final) {
        Equipo* campeon = (final->getGolesLocal() > final->getGolesVisitante()) ? final->getEquipoLocal() : final->getEquipoVisitante();
        Equipo* subcampeon = (campeon == final->getEquipoLocal()) ? final->getEquipoVisitante() : final->getEquipoLocal();
        cout << "Campeón:      " << campeon->getNombre() << endl;
        cout << "Subcampeón:   " << subcampeon->getNombre() << endl;

        if (tercerLugar) {
            Equipo* tercero = (tercerLugar->getGolesLocal() > tercerLugar->getGolesVisitante()) ? tercerLugar->getEquipoLocal() : tercerLugar->getEquipoVisitante();
            Equipo* cuarto = (tercero == tercerLugar->getEquipoLocal()) ? tercerLugar->getEquipoVisitante() : tercerLugar->getEquipoLocal();
            cout << "Tercer lugar: " << tercero->getNombre() << endl;
            cout << "Cuarto lugar: " << cuarto->getNombre() << endl;
        }
    } else {
        cout << "No hay información de la final."<<endl;
    }
    cout << endl;

    // 2. MÁXIMO GOLEADOR DEL EQUIPO CAMPEÓN
    if (final) {
        Equipo* campeon = (final->getGolesLocal() > final->getGolesVisitante()) ? final->getEquipoLocal() : final->getEquipoVisitante();
        // Obtener la lista de goleadores del campeon (punteros a Jugador)
        Lista<Jugador*> goleadoresCampeon = campeon->obtenerGoleadores();
        Jugador* maxGoleador = nullptr;
        unsigned short int maxGoles = 0;
        for (int i = 0; i < goleadoresCampeon.obtenerTamanio(); ++i) {
            Jugador* jug = goleadoresCampeon[i];
            unsigned short int goles = jug->getGoles();
            if (goles > maxGoles) {
                maxGoles = goles;
                maxGoleador = jug;
            }
        }
        cout << "2. MÁXIMO GOLEADOR DEL CAMPEÓN (" << campeon->getNombre() << "): "<<endl;
        if (maxGoleador) {
            cout << "   " << maxGoleador->getNombreCompleto() << " con " << maxGoles << " gol(es)."<<endl;
        } else {
            cout << " ---- "<<endl;
        }
        cout << endl;
    }

    // 3. TRES MAYORES GOLEADORES DEL TORNEO (versión eficiente con obtenerJugadores)
    struct GoleadorTop {
        Jugador* jugador;
        unsigned short int goles;
    };
    GoleadorTop top[3] = { {nullptr, 0}, {nullptr, 0}, {nullptr, 0} };

    const unsigned short int MAX_JUGADORES = 26;
    Jugador* jugadoresEquipo[MAX_JUGADORES];

    for (unsigned short int i = 0; i < totalEquipos; ++i) {
        Equipo* eq = equipos[i];
        if (!eq) continue;

        // Llenar el array con todos los jugadores del equipo (no solo goleadores)
        unsigned short int numJugadores = eq->obtenerJugadores(jugadoresEquipo, MAX_JUGADORES);

        for (unsigned short int j = 0; j < numJugadores; ++j) {
            Jugador* jug = jugadoresEquipo[j];
            if (!jug) continue;

            unsigned short int g = jug->getGoles();
            // Insertar en el top 3 (igual que antes)
            for (int k = 0; k < 3; ++k) {
                if (g > top[k].goles) {
                    // Desplazar hacia abajo los elementos menores
                    for (int l = 2; l > k; --l) {
                        top[l] = top[l-1];
                    }
                    top[k].jugador = jug;
                    top[k].goles = g;
                    break;
                }
            }
        }
    }

    cout << "3. TRES MAYORES GOLEADORES DEL TORNEO:\n";
    const char* medallas[3] = {"ORO", "PLATA", "BRONCE"};
    for (int i = 0; i < 3; ++i) {
        if (top[i].jugador) {
            cout << "   " << medallas[i] << " " << top[i].jugador->getNombreCompleto()
            << " (" << top[i].jugador->getGoles() << " goles)"<<endl;
        } else {
            cout << "   " << medallas[i] << " ----- "<<endl;
        }
    }
    cout << endl;

    //4. EQUIPO CON MÁS GOLES HISTORICOS (ACTUALIZADOS)
    Equipo* equipoMasGoles = nullptr;
    unsigned short int maxGolesHist = 0;
    for (unsigned short int i = 0; i < totalEquipos; ++i) {
        if (!equipos[i]) continue;
        unsigned short int goles = equipos[i]->getEstadisticas().getGolesFavor();
        if (goles > maxGolesHist) {
            maxGolesHist = goles;
            equipoMasGoles = equipos[i];
        }
    }
    cout << "4. EQUIPO CON MÁS GOLES HISTÓRICOS : "<<endl;
    if (equipoMasGoles) {
        cout << "   " << equipoMasGoles->getNombre() << " con " << maxGolesHist << " goles."<<endl;
    }
    else {
        cout << "   No hay información."<<endl;
    }
    cout << endl;

    // ========================== 5. CONFEDERACIÓN CON MAYOR PRESENCIA EN CADA ETAPA ==========================
    // Contadores: para R16, R8, R4 (los 4 mejores: semifinalistas)
    // Para R16: usamos los equipos que jugaron la ronda16.
    // Para R8: equipos que jugaron ronda8.
    // Para R4: equipos que jugaron semifinales (semis).
    // Como los arrays de partidos contienen los partidos, podemos extraer los equipos participantes.
    // Usaremos un mapa simple de confederación -> contador (como no podemos usar map, usamos arrays asociativos con búsqueda lineal, dado que hay pocas confederaciones).

    // Lista de confederaciones posibles (según el CSV: UEFA, CONMEBOL, CONCACAF, CAF, AFC, OFC)
    const char* confederaciones[] = {"UEFA", "CONMEBOL", "CONCACAF", "CAF", "AFC", "OFC"};
    const int NUM_CONF = 6;
    int contadoresR16[NUM_CONF] = {0};
    int contadoresR8[NUM_CONF] = {0};
    int contadoresR4[NUM_CONF] = {0};

    // Función auxiliar para incrementar contador de una confederación
    auto incrementar = [&](const string& conf, int* contadores) {
        for (int i = 0; i < NUM_CONF; ++i) {
            if (conf == confederaciones[i]) {
                contadores[i]++;
                break;
            }
        }
    };

    // Contar R16
    if (ronda16) {
        for (unsigned short int i = 0; i < numRonda16; ++i) {
            Partido* p = ronda16[i];
            if (p) {
                incrementar(p->getEquipoLocal()->getConfederacion(), contadoresR16);
                incrementar(p->getEquipoVisitante()->getConfederacion(), contadoresR16);
            }
        }
    }

    // Contar R8
    if (ronda8) {
        for (unsigned short int i = 0; i < numRonda8; ++i) {
            Partido* p = ronda8[i];
            if (p) {
                incrementar(p->getEquipoLocal()->getConfederacion(), contadoresR8);
                incrementar(p->getEquipoVisitante()->getConfederacion(), contadoresR8);
            }
        }
    }

    // Contar R4 (semifinalistas)
    if (semis) {
        for (unsigned short int i = 0; i < numSemis; ++i) {
            Partido* p = semis[i];
            if (p) {
                incrementar(p->getEquipoLocal()->getConfederacion(), contadoresR4);
                incrementar(p->getEquipoVisitante()->getConfederacion(), contadoresR4);
            }
        }
    }

    // Encontrar la confederación con máximo en cada etapa
    // Función auxiliar para obtener confederación con mayor presencia y su conteo
    // devuelve el nombre y la cantidad por referencia
    auto confMaxConValor = [&](int* contadores, string& nombre, int& cantidad) {
        int maxVal = 0;
        int idxMax = -1;
        for (int i = 0; i < NUM_CONF; ++i) {
            if (contadores[i] > maxVal) {
                maxVal = contadores[i];
                idxMax = i;
            }
        }
        if (idxMax >= 0) {
            nombre = confederaciones[idxMax];
            cantidad = maxVal;
        } else {
            nombre = "ninguna";
            cantidad = 0;
        }
    };

    string nombreR16;
    int cantidadR16;
    confMaxConValor(contadoresR16, nombreR16, cantidadR16);
    cout << "   - Ronda de 16 (R16): " << nombreR16 << " (" << cantidadR16 << " equipos)"<<endl;

    string nombreR8;
    int cantidadR8;
    confMaxConValor(contadoresR8, nombreR8, cantidadR8);
    cout << "   - Ronda de 8vos (R8): " << nombreR8 << " (" << cantidadR8 << " equipos)"<<endl;

    string nombreR4;
    int cantidadR4;
    confMaxConValor(contadoresR4, nombreR4, cantidadR4);
    cout << "    - Semifinales (R4): " << nombreR4 << " (" << cantidadR4 << " equipos)"<<endl;

    // ========================== 6. (OPCIONAL) MÉTRICAS DE EFICIENCIA ==========================
    // Si deseas mostrar las métricas de iteraciones y memoria al finalizar el torneo,
    // puedes incluir aquí la llamada a un método de medición (por ejemplo, ContadorMetricas::reportar())
    // Pero como no hemos implementado esa parte, lo dejamos comentado o lo agregamos más adelante.
    // cout << "6. CONSUMO DE RECURSOS:\n";
    // ContadorMetricas::reportar();

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║                      FIN DEL INFORME                         ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";
}

void Torneo::ejecutar() {
    simularFaseGrupos();
    transicionADieciseisavos();
    simularEliminatorias();
    generarInformeFinal();
}

#include "Partido.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;

Partido::Partido() : fecha(1,1,2026), hora(""), sede(""),
    equipoLocal(nullptr), equipoVisitante(nullptr),
    golesLocal(0), golesVisitante(0), posesionLocal(50.0f),
    prorroga(false), minutosPartido(90),
    numGoleadoresLocal(0), numGoleadoresVisitante(0)
{
    // Inicializar arbitros
    arbitros[0] = "codArbitro1";
    arbitros[1] = "codArbitro2";
    arbitros[2] = "codArbitro3";

    // Inicializar arrays de convocados = 0
    for (int i = 0; i < 11; ++i) {
        convocadosLocal[i] = 0;
        convocadosVisitante[i] = 0;
        goleadoresLocal[i] = 0;
        goleadoresVisitante[i] = 0;
    }
}

// Constructor x parametros
Partido::Partido(const Fecha& fecha, const string& hora, const string& sede, Equipo* local, Equipo* visitante)
    : fecha(fecha),
    hora(hora),
    sede(sede),
    equipoLocal(local),
    equipoVisitante(visitante),
    golesLocal(0),
    golesVisitante(0),
    posesionLocal(50.0f),
    prorroga(false),
    minutosPartido(90),
    numGoleadoresLocal(0),
    numGoleadoresVisitante(0)
{
    // Inicializar arbitros
    arbitros[0] = "codArbitro1";
    arbitros[1] = "codArbitro2";
    arbitros[2] = "codArbitro3";

    // Inicializar arrays de convocados = 0
    for (int i = 0; i < 11; ++i) {
        convocadosLocal[i] = 0;
        convocadosVisitante[i] = 0;
        goleadoresLocal[i] = 0;
        goleadoresVisitante[i] = 0;
    }
}


static unsigned short int poissonSample(float lambda)
{
    if (lambda <= 0.0f) return 0;
    float L = exp(-lambda);
    float p = 1.0f;
    unsigned short int k = 0;
    do {
        k++;
        p *= (static_cast<float>(rand()) / RAND_MAX);
    } while (p > L);
    return k - 1;
}


template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}


Partido::~Partido() {
    //Esta clase no se encarga de la eliminacion ni de equipos ni de jugadores
}



// Selecciona 11 jugadores aleatorios de la plantilla de cada equipo
void Partido::seleccionarConvocados()
{
    if (!equipoLocal || !equipoVisitante) return;

    // Paso 1: Obtener todos los jugadores del equipo local
    const unsigned short int TOTAL_JUGADORES = 26;
    Jugador* todosLocal[TOTAL_JUGADORES];
    unsigned short int numJugadoresLocal = equipoLocal->obtenerJugadores(todosLocal, TOTAL_JUGADORES);

    // Paso 2: Barajar ---> uso de swap
    for (unsigned short int i = numJugadoresLocal - 1; i > 0; --i) {
        unsigned short int j = rand() % (i + 1);
        std::swap(todosLocal[i], todosLocal[j]);
    }

    // Paso 3: Seleccionar primeros 11 y guardar sus numeros de camiseta
    for (int i = 0; i < 11 && i < numJugadoresLocal; ++i) {
        if (todosLocal[i] != nullptr) {
            convocadosLocal[i] = todosLocal[i]->getNumeroCamiseta();
        }
    }

    // Repetir para el equipo visitante
    Jugador* todosVisitante[TOTAL_JUGADORES];
    unsigned short int numJugadoresVisitante = equipoVisitante->obtenerJugadores(todosVisitante, TOTAL_JUGADORES);

    for (unsigned short int i = numJugadoresVisitante - 1; i > 0; --i) {
        unsigned short int j = rand() % (i + 1);
        std::swap(todosVisitante[i], todosVisitante[j]);
    }

    for (int i = 0; i < 11 && i < numJugadoresVisitante; ++i) {
        if (todosVisitante[i] != nullptr) {
            convocadosVisitante[i] = todosVisitante[i]->getNumeroCamiseta();
        }
    }
}


void Partido::calcularPosesion()
{
    if (!equipoLocal || !equipoVisitante) {
        posesionLocal = 50.0f;
        return;
    }

    int diferencia = static_cast<int>(equipoVisitante->getRanking()) - static_cast<int>(equipoLocal->getRanking());

    const float SENSIBILIDAD = 10.0f;  //valor ajustable

    float posesion = 50.0f + (diferencia / SENSIBILIDAD);

    // Limitar resultados extremos
    if (posesion < 30.0f) posesion = 30.0f;
    if (posesion > 70.0f) posesion = 70.0f;

    posesionLocal = posesion;
}



// Formula de goles esperados (ecuación 1 del enunciado)
float Partido::calcularGolesEsperados(Equipo* atacante, Equipo* defensor) const
{

    const float mu    = 1.35f;
    const float alpha = 0.6f;
    const float beta  = 0.4f;

    float gf = atacante->obtenerPromedioGolesFavor();
    float gc = defensor->obtenerPromedioGolesContra();

    float term1 = (gf / mu);
    float term2 = (gc / mu);
    float lambda = mu * powf(term1, alpha) * powf(term2, beta);

    // Acotar para evitar valores extremos
    if (lambda < 0.0f) lambda = 0.0f;
    if (lambda > 10.0f) lambda = 10.0f;
    return lambda;
}



// Distribuir los goles del equipo entre sus 11 convocados (probabilidad 4% por intento, hasta alcanzar golesEsperados)
void Partido::asignarGoles(Equipo* equipo, float lambda,
                           const unsigned short int* convocados,
                           unsigned short int* goleadores,
                           unsigned short int& numGoleadores,
                           Estadistica& statsEquipo)
{
    if (!equipo || !convocados) return;

    unsigned short int golesEquipo = poissonSample(lambda);
    if (golesEquipo == 0) return;

    unsigned short int golesAsignados = 0;
    const int MAX_JUGADORES = 11;
    const float PROB_GOL = 0.04f;
    int intentos = 0;

    while (golesAsignados < golesEquipo && intentos < 100) {
        for (int i = 0; i < MAX_JUGADORES && golesAsignados < golesEquipo; ++i) {
            float r = rand() / (float)RAND_MAX;
            if (r < PROB_GOL) {
                golesAsignados++;
                // Registrar goleador (numero de camiseta)
                goleadores[numGoleadores++] = convocados[i];
                // Actualizar estadisticas del equipo
                statsEquipo.actualizar(Estadistica(1, 0, 0, 0, 0, 0, 0, 0, 0, 0));

                Jugador* jug = equipo->obtenerJugadorPorNumero(convocados[i]);
                if (jug) {
                    Estadistica statsJugador(1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
                    jug->actualizarEstadisticas(statsJugador);
                }
            }
        }
        intentos++;
    }

    // X si las moscas si aun faltan goles (no deberia ocurrir), se asignan aleatoriamente
    if (golesAsignados < golesEquipo) {
        for (int j = 0; j < golesEquipo - golesAsignados; ++j) {
            int idx = rand() % MAX_JUGADORES;
            goleadores[numGoleadores++] = convocados[idx];
            statsEquipo.actualizar(Estadistica(1, 0, 0, 0, 0, 0, 0, 0, 0, 0));

            Jugador* jug = equipo->obtenerJugadorPorNumero(convocados[idx]);
            if (jug) {
                Estadistica statsJugador(1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
                jug->actualizarEstadisticas(statsJugador);
            }
        }
    }
}



void Partido::aplicarTarjetasYFaltasAJugador(Jugador* jugador, Estadistica& statsEquipo)
{
    if (!jugador) return;

    unsigned short int amarillas = 0;
    unsigned short int rojas = 0;
    unsigned short int faltas = 0;

    // Faltas (secuencial)
    float r = rand() / (float)RAND_MAX;
    // 1ra falta
    if (r < 0.13f) {
        faltas++;
        r = rand() / (float)RAND_MAX;
        // 2da falta
        if (r < 0.0275f) {
            faltas++;
            r = rand() / (float)RAND_MAX;
            // 3ra falta
            if (r < 0.007f) {
                faltas++;
            }
        }
    }

    // Tarjetas
    r = rand() / (float)RAND_MAX;
    // 1ra amarilla
    if (r < 0.06f) {
        amarillas = 1;
        r = rand() / (float)RAND_MAX;
        // 2da amarilla --> ROJA
        if (r < 0.0115f) {
            amarillas = 2;
            rojas = 1;
        }
    }

    // objeto temporal con los valores del partido (solo amarillas, rojas, faltas)
    Estadistica statsJugador(0, 0, 0, 0, 0, amarillas, rojas, faltas, 0, 0);
    jugador->actualizarEstadisticas(statsJugador);
    statsEquipo.actualizar(statsJugador);
}


void Partido::aplicarTarjetasYFaltas(Equipo* equipo, const unsigned short int* convocados, Estadistica& statsEquipo)
{
    for (int i = 0; i < 11; ++i) {
        unsigned short int numCamiseta = convocados[i];
        if (numCamiseta != 0) {
            Jugador* jug = equipo->obtenerJugadorPorNumero(numCamiseta);
            if (jug) {
                aplicarTarjetasYFaltasAJugador(jug, statsEquipo);
            }
        }
    }
}


void Partido::simular(bool esEliminatoria)
{
    // La semilla debe inicializarse en main()
    // Se asume que ya se llamo a srand(time(nullptr)) al inicio del programa.

    // 1. Elegir convocados aleatoriamente
    seleccionarConvocados();

    // 2. Calcular goles esperados (lambda) como float
    float lambdaLocal = calcularGolesEsperados(equipoLocal, equipoVisitante);
    float lambdaVisit = calcularGolesEsperados(equipoVisitante, equipoLocal);

    // 3. Asignar goles a los jugadores y acumular stats del equipo
    asignarGoles(equipoLocal, lambdaLocal, convocadosLocal,
                 goleadoresLocal, numGoleadoresLocal, statsLocalPartido);
    asignarGoles(equipoVisitante, lambdaVisit, convocadosVisitante,
                 goleadoresVisitante, numGoleadoresVisitante, statsVisitPartido);

    // 4. Aplicar tarjetas y faltas (ya actualiza jugadores y equipo)
    aplicarTarjetasYFaltas(equipoLocal, convocadosLocal, statsLocalPartido);
    aplicarTarjetasYFaltas(equipoVisitante, convocadosVisitante, statsVisitPartido);

    // 5. Calcular posesion
    calcularPosesion();

    // 6. Guardar goles finales
    golesLocal = statsLocalPartido.getGolesFavor();
    golesVisitante = statsVisitPartido.getGolesFavor();

    // 7. Desempate en eliminatorias
    if (esEliminatoria && golesLocal == golesVisitante) {
        prorroga = true;
        minutosPartido = 120;

        unsigned short rLocal = equipoLocal->getRanking();
        unsigned short rVisit = equipoVisitante->getRanking();
        float probLocal = static_cast<float>(rVisit) / (rLocal + rVisit);
        float rnd = rand() / (float)RAND_MAX;

        if (rnd < probLocal) {
            statsLocalPartido.actualizar(Estadistica(1,0,0,0,0,0,0,0,0,0));
            golesLocal++;
        } else {
            statsVisitPartido.actualizar(Estadistica(1,0,0,0,0,0,0,0,0,0));
            golesVisitante++;
        }
    }
}



void Partido::actualizarHistoricos() {
    // Actualizar estadisticas de los equipos
    equipoLocal->actualizarEstadisticas(statsLocalPartido);
    equipoVisitante->actualizarEstadisticas(statsVisitPartido);

    // asignar minutos jugados (90 o 120) a cada convocado.
    for (int i = 0; i < 11; ++i) {
        if (convocadosLocal[i] != 0) {
            Jugador* jug = equipoLocal->obtenerJugadorPorNumero(convocadosLocal[i]);
            if (jug) {
                Estadistica statsMinutos(0,0,0,0,0,0,0,0, minutosPartido, 0);
                jug->actualizarEstadisticas(statsMinutos);
            }
        }
        if (convocadosVisitante[i] != 0) {
            Jugador* jug = equipoVisitante->obtenerJugadorPorNumero(convocadosVisitante[i]);
            if (jug) {
                Estadistica statsMinutos(0,0,0,0,0,0,0,0, minutosPartido, 0);
                jug->actualizarEstadisticas(statsMinutos);
            }
        }
    }
}


// Getters
Equipo* Partido::getEquipoLocal() const { return equipoLocal; }
Equipo* Partido::getEquipoVisitante() const { return equipoVisitante; }
unsigned short int Partido::getGolesLocal() const { return golesLocal; }
unsigned short int Partido::getGolesVisitante() const { return golesVisitante; }
float Partido::getPosesionLocal() const { return posesionLocal; }
bool Partido::hayProrroga() const { return prorroga; }


void Partido::imprimirResumen() const {
    cout << "Fecha: " << fecha << " Hora: " << hora << " Sede: " << sede << endl;
    cout << equipoLocal->getNombre() << " " << golesLocal << " - " << golesVisitante << " " << equipoVisitante->getNombre() << endl;
    cout << "Posesión: " << posesionLocal << "% - " << (100.0f - posesionLocal) << "%" << endl;
    if (prorroga) cout << "(Prórroga - " << minutosPartido << " minutos)" << endl;
    cout << "Goleadores local: ";
    for (int i = 0; i < numGoleadoresLocal; ++i) cout << goleadoresLocal[i] << " ";
    cout << endl;
    cout << "Goleadores visitante: ";
    for (int i = 0; i < numGoleadoresVisitante; ++i) cout << goleadoresVisitante[i] << " ";
    cout << endl;
}

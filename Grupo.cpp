#include "Grupo.h"

Grupo::Grupo() {
    for(int i=0;i<4;++i){
        equipos[i]=nullptr;
    }
    for(int i=0;i<6;++i){
        partidos[i]=nullptr;
    }
}

void Grupo::generarFixture(Fecha fechaInicio){
    unsigned short int conta_partidos=0;
    for (unsigned short int i=0;i<6;++i){
        for (unsigned short int j=i+1 ;i<4;i++){
            partidos[conta_partidos]=new Partido(equipos[i],equipos[j]);
            partidos[conta_partidos]->setFecha(fechaInicio);
            if (conta_partidos % 2 != 0) {
                fechaInicio.sumarDias(4);
            }
            ++conta_partidos;
        }
    }
}

void Grupo:: jugarPartidos(){


}
class Grupo {
private:
    char letra;
    Equipo* equipos[4];
    Partido* partidos[6];

public:
    Grupo();
    void generarFixture(Fecha fechaInicio);
    void jugarPartidos();
    void obtenerTablaPosiciones();
    Lista<Equipo*> obtenerMejoresTerceros();
};

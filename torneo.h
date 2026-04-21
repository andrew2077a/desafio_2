#ifndef TORNEO_H
#define TORNEO_H

class Torneo{
private:
    Grupo grupos[12];
    Partido* ronda16[16];
    Partido* ronda8[8];
    Partido* cuartos[4];
    Partido* semis[2];
    partid* final ;

public:
    torneo();
};

#endif // TORNEO_H

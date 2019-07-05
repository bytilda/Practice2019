#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "object.h"




class Transport : public Object
{
public:
    Transport();
    Transport(double x, double y, double ax, double ay, Map *m);
    void  nextStep(double dt) override;
    int getColor();
    int getX();
    int getY();
    double getAx();
    double getAy();
    bool isCrashed();
    void crash();
    void deathf();


protected:
    int chooseWay(int var);
    double vx; //скорость по оси х
    double vy; //скорость по оси у
    double ax, ay; //ускорение    
    int newa;
    int color;    
    int currDirection;
    int nextDirection;
    int destToNextDirection = 0;
    int primordialDest = 0;
    int choosenWay = 0;
    bool crashed = false;
    int crashedTime = 0;


};

#endif // TRANSPORT_H

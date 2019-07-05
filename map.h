#ifndef MAP_H
#define MAP_H
#include "object.h"
#include <QString>
//#include <iostream>
#include <fstream>
#include "string.h"
#include "QDebug"
#include "QFile"
#include "car.h"
#include <vector>
#include "enums.h"
//#include "generationpoint.h"

//class generationPoint;

#define CELL_SIZE 10
//enum obj {empty, roadu, roadr, roadd, roadl, border = 99, car = 100, bus = 101};

class Map
{
private:
    double timePassed = 0;
    void recCore(int x, int y, int dx, int dy, int &dest, int &nextReasonToStop, int choosenWay1, Object* &reas, int &destToObj);
    bool carCrashing = false;
    int streamLevel = 1;


public:
    Map();
    std::vector<Object*> vobj;
    Object* movableObjects[100][100] = {};
    int unmovableObjects[100][100] = {};

    void ReadMap();
    void NextStep(double dt);
    void getInformation(int &direction, int x, int y, int &dest, int choosenWay, Object* &reas, int &destToObj);
    double getTime();
    int amOfGP = 0;
    void setStreamLevel(int val);
    int getStreamLevel();
    void setCarCrashing(bool val);
    bool getCarCrashing();

    //friend void f(Transport* tr);
    //friend class Transport;
};



#endif // MAP_H

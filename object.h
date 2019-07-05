#ifndef OBJECT_H
#define OBJECT_H
//#include "enums.h"

//#include "map.h"
class Map;

 class Object
{
protected:
     Map* map;
    //int priority;
    double x;
    double y;
    int type;

public:
    Object();
    Object(double x, double y, Map* m);
    ~Object();
    void virtual nextStep(double dt) = 0;
    int getType();
};

#endif // OBJECT_H

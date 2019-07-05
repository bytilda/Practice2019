#ifndef CAR_H
#define CAR_H
#include "transport.h"

class Car : public Transport
{
public:
    Car();
    Car(int x, int y, double ax, double ay, Map *m);
};

#endif // CAR_H

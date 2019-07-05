#include "car.h"

Car::Car()
{

}

Car::Car(int x, int y, double ax, double ay, Map *m):Transport (x, y, ax, ay, m){
    type = 100;



}
